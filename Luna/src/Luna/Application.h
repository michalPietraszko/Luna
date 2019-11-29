#pragma once
#include "Core.h"
#include "Luna/Events/ApplicationEvent.h"
#include "Luna/LayerStack.h"
#include "Luna/Events/Event.h"
#include "Luna/Events/ApplicationEvent.h"
#include "Window.h"

namespace Luna
{
	class LUNA_API ExampleLayer : public Layer
	{
	public:
		ExampleLayer()
			: Layer("Example") {}

		void onUpdate() override
		{
			//LN_CORE_INFO("ExampleLayer::Update");
		}

		void onEvent(Luna::Event& event) override
		{
			LN_CORE_TRACE("{0}", event);
		}
	};

class LUNA_API Application
{
public:
	Application();
	virtual ~Application();
	void run();
	void onEvent(Event& e);
protected:
	LayerStack::LayerProxy pushLayer(std::unique_ptr<Layer> layer);
	LayerStack::LayerProxy pushOverlay(std::unique_ptr<Layer> layer);
public:
	template<typename T>
	void pushLayer()
	{
		prx = pushLayer(Layer::createLayer<T>());
	}
	
	void popLayer(LayerStack::LayerProxy&& prx) { m_LayerStack.pop(std::move(prx)); }
	bool test{ false };
private:
	bool onWindowClose(WindowCloseEvent& e);
	
	std::unique_ptr<Window> m_Window;
	LayerStack& m_LayerStack;
	LayerStack::LayerProxy&& prx{};
	bool m_Running{true};
};

// To be defined in CLIENT
Application* createApplication();

}// namespace
