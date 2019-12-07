#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Luna/Events/ApplicationEvent.h"
#include "Luna/LayerStack.h"

namespace Luna
{
class LUNA_API Application
{
public:
	Application();
	virtual ~Application();
	void run();
	void onEvent(Event& e);
	void pushLayer(Layer* layer);
	void pushOverlay(Layer* layer);

private:
	bool onWindowClose(WindowCloseEvent& e);

private:
	std::unique_ptr<Window> m_Window;
	bool m_Running{true};
	LayerStack& m_LayerStack;
};

// To be defined in CLIENT
Application* createApplication();

}// namespace
