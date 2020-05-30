#include "lnpch.h"
#include "Application.h"

#include "Luna/Log.h"
#include "Input.h"
#include "Luna/Renderer/Renderer.h"

namespace Luna
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::s_Instance = nullptr;

Application::Application() : m_LayerStack{LayerStack::instance()}
{
    LN_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::create());
    m_Window->setEventCallback(BIND_EVENT_FN(onEvent));

    auto temp = std::make_unique<ImGuiLayer>();
    m_ImGuiLayer = temp.get();
    pushOverlay(std::move(temp));

    openGLBs();
}

void Application::openGLBs()
{
    m_VertexArray.reset(VertexArray::create());

    float vertices[3 * 7] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, 0.5f, -0.5f, 0.0f, 0.2f,
                             0.3f,  0.8f,  1.0f, 0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f,  1.0f};

    std::shared_ptr<VertexBuffer> vertexBuffer;
    vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
    BufferLayout layout = {{ShaderDataType::Float3, "a_Position"}, {ShaderDataType::Float4, "a_Color"}};
    vertexBuffer->setLayout(layout);
    m_VertexArray->addVertexBuffer(vertexBuffer);

    uint32_t indices[3] = {0, 1, 2};
    std::shared_ptr<IndexBuffer> indexBuffer;
    indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
    m_VertexArray->setIndexBuffer(indexBuffer);

    m_SquareVA.reset(VertexArray::create());

    // clang-format off
    float squareVertices[3 * 4] = {
 			-0.75f, -0.75f, 0.0f,
 			 0.75f, -0.75f, 0.0f,
 			 0.75f,  0.75f, 0.0f,
 			-0.75f,  0.75f, 0.0f
 	};

    std::shared_ptr<VertexBuffer> squareVB;
    squareVB.reset(VertexBuffer::create(squareVertices, sizeof(squareVertices)));
    squareVB->setLayout({
        { ShaderDataType::Float3, "a_Position"}
    }); // clang-format on
    m_SquareVA->addVertexBuffer(squareVB);

    uint32_t squareIndicies[6] = {0, 1, 2, 2, 3, 0};
    std::shared_ptr<IndexBuffer> squareIB;
    squareIB.reset(IndexBuffer::create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
    m_SquareVA->setIndexBuffer(squareIB);

    std::string vertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);    
            }
         )";

    std::string fragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
         )";

    m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

    std::string blueShaderVertexSrc = R"(
 			#version 330 core
 			
 			layout(location = 0) in vec3 a_Position;

 			out vec3 v_Position;

 			void main()
 			{
 				v_Position = a_Position;
 				gl_Position = vec4(a_Position, 1.0);	
 			}
 		)";

    std::string blueShaderFragmentSrc = R"(
 			#version 330 core
 			
 			layout(location = 0) out vec4 color;

 			in vec3 v_Position;

 			void main()
 			{
 				color = vec4(0.2, 0.3, 0.8, 1.0);
 			}
 		)";

    m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
}

Application::~Application() = default;

void Application::onEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
    {
        (*--it)->onEvent(e);
        if (e.m_Handled)
        {
            break;
        }
    }
}

// inline
LayerStack::const_iterator Application::pushOverlay(std::unique_ptr<Layer> layer)
{
    return m_LayerStack.pushOverlay(std::move(layer));
}

// inline
LayerStack::const_iterator Application::pushLayer(std::unique_ptr<Layer> layer)
{
    return m_LayerStack.pushLayer(std::move(layer));
}

void Application::run()
{
    while (m_Running)
    {
        RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
        RenderCommand::clear();

        Renderer::beginScene();

        m_BlueShader->bind();
        Renderer::submit(m_SquareVA);

        m_Shader->bind();
        Renderer::submit(m_VertexArray);

        Renderer::endScene();

        for (auto&& layer : m_LayerStack)
            layer->onUpdate();

        m_ImGuiLayer->begin();
        for (auto&& layer : m_LayerStack)
            layer->onImGuiRender();
        m_ImGuiLayer->end();

        m_Window->onUpdate();
    }
}

bool Application::onWindowClose(WindowCloseEvent& e)
{
    m_Running = false;
    return true;
}
} // namespace Luna
