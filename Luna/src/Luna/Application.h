#pragma once
#include "Core.h"
#include "Luna/Events/ApplicationEvent.h"
#include "Luna/LayerStack.h"
#include "Luna/Events/Event.h"
#include "Luna/Events/ApplicationEvent.h"
#include "Window.h"

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
    void popoverlay(LayerStack::const_iterator&& prx) { m_LayerStack.popOverlay(std::move(prx)); }

private:
    bool onWindowClose(WindowCloseEvent& e);

private:
    bool m_Running{true};
    std::unique_ptr<Window> m_Window;
    LayerStack& m_LayerStack;

private:
    static Application* s_Instance;
};

// To be defined in CLIENT
Application* createApplication();

} // namespace Luna
