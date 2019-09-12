#include "Application.h"

#include "Luna/Events/ApplicationEvent.h"
#include "Luna/Log.h"

namespace Luna
{
	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::run()
	{	
		WindowResizeEvent e(1280, 720);
		LN_TRACE(e);
		
		while (true);
	}
} // namespace
