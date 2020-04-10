#include <Luna.h>

class ExampleLayer : public Luna::Layer
{
public:
    ExampleLayer() : Layer("Example") {}

	void onUpdate() override
 	{
 		if (Luna::Input::isKeyPressed(LN_KEY_TAB))
 			LN_TRACE("Tab key is pressed (poll)!");
 	}

 	void onEvent(Luna::Event& event) override
 	{
 		if (event.getEventType() == Luna::EventType::KeyPressed)
 		{
 			auto& e = (Luna::KeyPressedEvent&)event;
 			if (e.getKeyCode() == LN_KEY_TAB)
 				LN_TRACE("Tab key is pressed (event)!");
 			LN_TRACE("{0}", (char)e.getKeyCode());
 		}
 	}
};

class Sandbox : public Luna::Application
{
public:
    Sandbox()
    {
        pushLayer(std::make_unique<ExampleLayer>());
        pushOverlay(std::make_unique<Luna::ImGuiLayer>());
    }
    ~Sandbox() {}
};

Luna::Application* Luna::createApplication()
{
    return new Sandbox();
}