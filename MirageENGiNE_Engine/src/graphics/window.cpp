#include "window.h"

// lib includes
#include <GLFW/glfw3.h>

// mirage includes
#include "config.h"
#include "macros.h"

namespace mirage
{

	Window::Window(
		const std::string title,
		int width,
		int height,
		bool fullscreen
	) :
		m_window(NULL),
		m_title(title)
	{
		// Setup GLFW window hints
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_CONTEXT_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_CONTEXT_MINOR);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);

		// Create the window, inform errors
		m_window = glfwCreateWindow(width, height, m_title.c_str(), (fullscreen == true) ? glfwGetPrimaryMonitor() : NULL, NULL);

		// Throw exception if glfwCreateWindow returns NULL
		if (m_window == NULL)
			throw std::exception("Window::Window glfwCreateWindow failed.");

		// Create GL context for this window, make it current and so on...
		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(GL_SWAP_INTERVAL);
		glfwShowWindow(m_window);

		MLOG_INFO("Window::Window, created. Title: %s, width: %d, height: %d, fullscreen: %s", m_title.c_str(), width, height, (fullscreen == true) ? "true" : "false");
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
	}

	GLFWwindow * const Window::getHandle() const
	{
		return m_window;
	}

	void Window::setTitle(const std::string title)
	{
		glfwSetWindowTitle(m_window, title.c_str());
		m_title = title;
	}

	std::string Window::getTitle() const
	{
		return m_title;
	}

	void Window::setWidth(int width)
	{
		glfwSetWindowSize(m_window, width, getHeight());
	}

	int Window::getWidth() const
	{
		int w = 0, h = 0;
		glfwGetWindowSize(m_window, &w, &h);
		return w;
	}

	void Window::setHeight(int height)
	{
		glfwSetWindowSize(m_window, getWidth(), height);
	}

	int Window::getHeight() const
	{
		int w = 0, h = 0;
		glfwGetWindowSize(m_window, &w, &h);
		return h;
	}

}