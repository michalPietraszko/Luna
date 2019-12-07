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

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->onEvent(e);
			if (e.m_Handled) 
			{
				break;
			}
		}
	}

	// inline
	LayerStack::LayerProxy Application::pushOverlay(std::unique_ptr<Layer> layer)
 	{
 		return m_LayerStack.pushOverlay(std::move(layer));
 	}

	// inline
	LayerStack::LayerProxy Application::pushLayer(std::unique_ptr<Layer> layer)
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

			m_Window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
} // namespace
