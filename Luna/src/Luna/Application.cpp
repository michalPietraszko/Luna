#include "lnpch.h"
#include "Application.h"

#include "Luna/Log.h"
#include "Input.h"
#include <glad/glad.h>

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
    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    float vertices[3 * 3] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    m_VertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    uint32_t indices[3] = {0, 1, 2};
    m_IndexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));

    std::string vertexSrc = R"(
             #version 330 core
             
             layout(location = 0) in vec3 a_Position;

             out vec3 v_Position;

             void main()
             {
                 v_Position = a_Position;
                 gl_Position = vec4(a_Position, 1.0);    
             }
         )";

    std::string fragmentSrc = R"(
             #version 330 core
             
             layout(location = 0) out vec4 color;

             in vec3 v_Position;

             void main()
             {
                 color = vec4(v_Position * 0.5 + 0.5, 1.0);
             }
         )";

    m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
}

Application::~Application() {}

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
        glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Shader->bind();
        glBindVertexArray(m_VertexArray);
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

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
