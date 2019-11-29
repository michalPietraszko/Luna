#include <Luna.h>

class Sandbox : public Luna::Application 
{
public:
	Sandbox() {
		pushLayer<Luna::ExampleLayer>();
	}
	~Sandbox() {}
};

Luna::Application* Luna::createApplication()
{
	return new Sandbox();
}