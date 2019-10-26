#pragma once

#pragma once

#include "Luna/Window.h"

#include <GLFW/glfw3.h>

namespace Luna
{

class WindowsWindow : public Window
{
	struct WindowData
	{
		WindowData(const Window::WindowProps& properties)
			: title(properties.title), width(properties.width), height(properties.height) {}

		std::string title;
		unsigned int width;
		unsigned int height;
		bool vSync;

		EventCallbackFn eventCallback;
	};

public:
	// todo check if needed
	WindowsWindow(const WindowProps &props);
	virtual ~WindowsWindow();

	void onUpdate() override;

	inline unsigned int getWidth() const override { return m_Data.width; }
	inline unsigned int getHeight() const override { return m_Data.height; }

	// Window attributes
	inline void setEventCallback(const EventCallbackFn &callback) override
	{
		m_Data.eventCallback = callback;
	}

	void setVSync(bool enabled) override;
	bool isVSync() const override;

private:
	void setGlfwCallbacks();
	virtual void init(const WindowProps &props);
	virtual void shutdown();

private:
	GLFWwindow *m_Window;
	WindowData m_Data;
};

} // namespace Luna
