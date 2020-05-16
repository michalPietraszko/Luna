#pragma once
#include "Core.h"
#include "Luna/Events/ApplicationEvent.h"
#include "Luna/LayerStack.h"
#include "Luna/Events/Event.h"
#include "Luna/Events/ApplicationEvent.h"
#include "Luna/ImGui/ImGuiLayer.h"
#include "Window.h"
#include "Luna/Renderer/Shader.h"
#include "Luna/Renderer/Buffer.h"
#include "Luna/Renderer/VertexArray.h"

namespace Luna
{
class LUNA_API Application
{
public:
    Application();
    virtual ~Application();

    void run();
    void onEvent(Event& e);
    Window& getWindow() { return *m_Window; }
    static Application& get() { return *s_Instance; }

protected:
    LayerStack::const_iterator pushLayer(std::unique_ptr<Layer> layer);
    LayerStack::const_iterator pushOverlay(std::unique_ptr<Layer> layer);
    void popLayer(LayerStack::const_iterator&& prx) { m_LayerStack.popLayer(std::move(prx)); }
    void popOverlay(LayerStack::const_iterator&& prx) { m_LayerStack.popOverlay(std::move(prx)); }

    void openGLBs();

private:
    bool onWindowClose(WindowCloseEvent& e);

private:
    bool m_Running{true};
    std::unique_ptr<Window> m_Window;

    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<VertexArray> m_VertexArray;

    std::shared_ptr<Shader> m_BlueShader;
    std::shared_ptr<VertexArray> m_SquareVA;

    ImGuiLayer* m_ImGuiLayer;
    LayerStack& m_LayerStack;

private:
    static Application* s_Instance;
};

// To be defined in CLIENT
Application* createApplication();

} // namespace Luna
