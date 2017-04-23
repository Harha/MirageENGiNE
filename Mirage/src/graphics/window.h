#ifndef WINDOW_H
#define WINDOW_H

// std includes
#include <string>

typedef struct GLFWwindow GLFWwindow;

namespace mirage
{

	class Window
	{
	public:
		Window(const std::string t = "window", int w = 1280, int h = 720, bool fs = false);
		~Window();
		void setTitle(const std::string t);
		std::string getTitle() const;
		int getWidth() const;
		int getHeight() const;
		GLFWwindow * const getHandle() const;
	private:
		GLFWwindow * m_window;
		std::string m_title;
	};

}

#endif // WINDOW_H