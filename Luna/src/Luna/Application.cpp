#include "lnpch.h"
#include "Application.h"

#include "Luna/Events/ApplicationEvent.h"
#include "Luna/Log.h"

#include <GLFW/glfw3.h>

namespace Luna
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::create());
	}

	Application::~Application()
	{
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
} // namespace
