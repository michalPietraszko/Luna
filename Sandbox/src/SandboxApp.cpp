#include <Luna.h>

class ExampleLayer : public Luna::Layer
 {
 public:
 	ExampleLayer()
 		: Layer("Example")
 	{
 	}

  	void OnUpdate() override
 	{
 		LN_INFO("ExampleLayer::Update");
 	}

  	void OnEvent(Hazel::Event& event) override
 	{
 		LN_TRACE("{0}", event);
 	}
  };

class Sandbox : public Luna::Application 
{
public:
	Sandbox() { pushLayer(new ExampleLayer());}
	~Sandbox() {}
};

Luna::Application* Luna::createApplication()
{
	return new Sandbox();
}