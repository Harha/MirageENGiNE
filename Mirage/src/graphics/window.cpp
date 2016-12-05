#include "window.h"

// lib includes
#include <GLFW/glfw3.h>

// mirage includes
#include "config.h"
#include "macros.h"

namespace mirage
{

	Window::Window(const std::string t, int w, int h, bool fs) :
		m_window(NULL)
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
		m_window = glfwCreateWindow(w, h, t.c_str(), (fs == true) ? glfwGetPrimaryMonitor() : NULL, NULL);

		if (m_window == NULL)
			throw std::exception("Window::Window glfwCreateWindow failed.");

		// Create GL context, bind it to the window, etc...
		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(GL_SWAP_INTERVAL);
		glfwShowWindow(m_window);

		MLOG_INFO("Window::Window initialized successfully. Title: %s, width: %d, height: %d, fullscreen: %s", t.c_str(), w, h, (fs == true) ? "true" : "false");
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
	}

	void Window::setTitle(const std::string t)
	{
		glfwSetWindowTitle(m_window, t.c_str());
	}

	int Window::getWidth() const
	{
		int w = 0, h = 0;
		glfwGetWindowSize(m_window, &w, &h);
		return w;
	}

	int Window::getHeight() const
	{
		int w = 0, h = 0;
		glfwGetWindowSize(m_window, &w, &h);
		return h;
	}

	GLFWwindow * const Window::getHandle() const
	{
		return m_window;
	}

}