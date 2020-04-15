#include "lnpch.h"
#include "WindowsWindow.h"

#include "Luna/Events/ApplicationEvent.h"
#include "Luna/Events/MouseEvent.h"
#include "Luna/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Luna
{
static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* descript)
{
    LN_CORE_ERROR("GLFW Error ({0}): {1}", error, descript);
}

Window* Window::create(const WindowProps& props)
{
    return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props) : m_Data(props)
{
    init(props);
}

WindowsWindow::~WindowsWindow()
{
    shutdown();
}

void WindowsWindow::setGlfwCallbacks()
{
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.eventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.eventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action)
        {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key, 0);
                data.eventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                data.eventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event(key, 1);
                data.eventCallback(event);
                break;
            }
        }
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action)
        {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(button);
                data.eventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(button);
                data.eventCallback(event);
                break;
            }
        }
    });

    glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        KeyTypedEvent event(keycode);
        data.eventCallback(event);
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.eventCallback(event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)xPos, (float)yPos);
        data.eventCallback(event);
    });
}

void WindowsWindow::init(const WindowProps& props)
{
    LN_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

    if (!s_GLFWInitialized)
    {
        // TODO: glfwTerminate on system shutdown
        const int success = glfwInit();
        LN_CORE_ASSERT(success, "Could not intialize GLFW!");

        glfwSetErrorCallback(GLFWErrorCallback);
        s_GLFWInitialized = true;
    }

    constexpr GLFWmonitor* monitor = nullptr;
    constexpr GLFWwindow* share = nullptr;

    m_Window = glfwCreateWindow(
        static_cast<int>(props.width), static_cast<int>(props.height), m_Data.title.c_str(), monitor, share);

    m_Context = new OpenGLContext(m_Window); // memory leak? run valgrind
    m_Context->init();

    glfwSetWindowUserPointer(m_Window, &m_Data);
    setVSync(true);

    // Set GLFW callbacks
    setGlfwCallbacks();
}

void WindowsWindow::shutdown()
{
    glfwDestroyWindow(m_Window);
}

void WindowsWindow::onUpdate()
{
    glfwPollEvents();
    m_Context->swapBuffers();
}

void WindowsWindow::setVSync(bool enabled)
{
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    m_Data.vSync = enabled;
}

bool WindowsWindow::isVSync() const
{
    return m_Data.vSync;
}

} // namespace Luna