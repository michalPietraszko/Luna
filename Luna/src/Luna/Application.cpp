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
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

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
