
#pragma once

#include "lnpch.h"

#include "Luna/Core.h"
#include "Luna/Events/Event.h"

namespace Luna
{
// Interface representing a desktop system based Window
class LUNA_API Window
{
public:
    struct WindowProps
    {
        WindowProps(const std::string& title = "Luna Engine", unsigned int width = 1280, unsigned int height = 720)
            : title(title), width(width), height(height)
        {
        }

        std::string title;
        unsigned int width;
        unsigned int height;
    };

    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() {}

    virtual void onUpdate() = 0;

    virtual unsigned int getWidth() const = 0;
    virtual unsigned int getHeight() const = 0;

    // Window attributes
    virtual void setEventCallback(const EventCallbackFn& callback) = 0;
    virtual void setVSync(bool enabled) = 0;
    virtual bool isVSync() const = 0;

    static Window* create(const WindowProps& props = WindowProps());
};
} // namespace Luna
