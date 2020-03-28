#include <Luna.h>

class ExampleLayer : public Luna::Layer
{
public:
    ExampleLayer() : Layer("Example") {}

    void onUpdate() override
    {
        //	LN_INFO("ExampleLayer::Update");
    }

    void onEvent(Luna::Event& event) override { LN_TRACE("{0}", event); }
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