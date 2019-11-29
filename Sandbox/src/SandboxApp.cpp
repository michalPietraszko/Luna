#include <Luna.h>

class ExampleLayer : public Luna::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void onUpdate() override
	{
		LN_INFO("ExampleLayer::Update");
	}

	void onEvent(Luna::Event& event) override
	{
	//	auto eventName = event.toString();
	//	std::cout << eventName << std::endl;
		std::cout << "dwwd" << std::endl;

		
		//LN_INFO("ExampleLayer::Upd33333ate {0}", eventName);
		//int i;
	}

	void kupa(const std::string& ii) override
	{
		std::cout << "d33wwd " << ii << std::endl;

	}
};

class Sandbox : public Luna::Application 
{
public:
	Sandbox() {
		auto ptr = std::make_unique<ExampleLayer>();
		pushLayer(std::move(ptr));
	}
	~Sandbox() {}
};

Luna::Application* Luna::createApplication()
{
	return new Sandbox();
}