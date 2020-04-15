#include "lnpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Luna
{
OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle{windowHandle}
{
    LN_CORE_ASSERT(windowHandle, "Window handle is null!")
}

void OpenGLContext::init()
{
    glfwMakeContextCurrent(m_WindowHandle);
    const int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    LN_CORE_ASSERT(status, "Failed to initialize Glad!");

    LN_CORE_INFO("OpenGL Info:");
    LN_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
    LN_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
    LN_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
}

void OpenGLContext::swapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}
} // namespace Luna