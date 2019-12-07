#include "lnpch.h"
#include "Application.h"
#include "Luna/Log.h"

#include <GLFW/glfw3.h>

namespace Luna
{	
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() : m_LayerStack{LayerStack::instance()}
	{
		m_Window = std::unique_ptr<Window>(Window::create());
		m_Window -> setEventCallback(BIND_EVENT_FN(onEvent));
	}

	Application::~Application()
	{
	}

	void Application::propagateEventDownLayerStack(Event& event)
	{
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++)
 		{
 			(*it)->OnEvent(e);
 			if (e.m_Handled)
 				break;
 		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		LN_CORE_TRACE("{0}", e);

		propagateEventDownLayerStack(e);
	}

	void Application::pushLayer(Layer* layer)
	{
		m_LayerStack.push(layer);
	}

	void Application::pushOverlay(Layer* overlay)
	{
		m_LayerStack.push(overlay);
	}

	void Application::run()
	{	
		// WindowResizeEvent e(1280, 720);
		// LN_TRACE(e);
		
		while (m_Running)
		{	
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->onUpdate();

			for (auto* layer : m_LayerStack)
 				layer->OnUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
} // namespace
