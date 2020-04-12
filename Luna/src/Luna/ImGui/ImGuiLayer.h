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

    virtual void onAttach() override;
    virtual void onDetach() override;
    virtual void onImGuiRender() override;

    void begin();
    void end();

private:
    float m_Time = 0.0f;
};

} // namespace Luna