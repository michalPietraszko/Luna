#pragma once

#include "Luna/Layer.h"
#include "Luna/Events/ApplicationEvent.h"
#include "Luna/Events/KeyEvent.h"
#include "Luna/Events/MouseEvent.h"

namespace Luna
{
class LUNA_API ImGuiLayer : public Layer
{
public:
    ImGuiLayer();
    ~ImGuiLayer();

    void onAttach() override;
    void onDetach() override;
    void onUpdate() override;
    void onEvent(Event& event) override;

private:
    bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
    bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
    bool onMouseMovedEvent(MouseMovedEvent& e);
    bool onMouseScrolledEvent(MouseScrolledEvent& e);
    bool onKeyPressedEvent(KeyPressedEvent& e);
    bool onKeyReleasedEvent(KeyReleasedEvent& e);
    bool onKeyTypedEvent(KeyTypedEvent& e);
    bool onWindowResizeEvent(WindowResizeEvent& e);

private:
    float m_Time = 0.0f;
};

} // namespace Luna