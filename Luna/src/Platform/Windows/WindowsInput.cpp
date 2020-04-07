#include "lnpch.h"
#include "WindowsInput.h"

#include "Luna/Application.h"
#include <GLFW/glfw3.h>

namespace Luna
{
Input* Input::s_Instance = new WindowsInput();

bool WindowsInput::isKeyPressedImpl(int keycode)
{
    auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::isMouseButtonPressedImpl(int button)
{
    auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> WindowsInput::getMousePositionImpl()
{
    auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return {static_cast<float>(xpos), static_cast<float>(ypos)};
}

float WindowsInput::getMouseXImpl()
{
    return getMousePositionImpl().first;
}

float WindowsInput::getMouseYImpl()
{
    return getMousePositionImpl().second;
}

} // namespace Luna