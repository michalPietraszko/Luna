#pragma once

#include "Luna/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Luna
{
class OpenGLContext : public GraphicsContext
{
public:
    OpenGLContext(GLFWwindow* windowHandle);

    virtual void init() override;
    virtual void swapBuffers() override;

private:
    GLFWwindow* m_WindowHandle;
};

} // namespace Luna