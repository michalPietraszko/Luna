#include "lnpch.h"
#include "Application.h"

#include "Luna/Log.h"

#include <GLFW/glfw3.h>

namespace Luna
{	
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()  : m_LayerStack{LayerStack::instance()}
	{
		m_Window = std::unique_ptr<Window>(Window::create());
		m_Window -> setEventCallback(BIND_EVENT_FN(onEvent));
	}

	Application::~Application()
	{
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		LN_CORE_TRACE("{0}", e);
	}

	// inline
	void Application::pushLayer(std::unique_ptr<Layer> layer)
 	{
 		m_LayerStack.PushLayer(std::move(layer));
 	}

	// inline
  	void Application::PushOverlay(std::unique_ptr<Layer> layer)
 	{
 		m_LayerStack.PushOverlay(std::move(layer));
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
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
} // namespace
