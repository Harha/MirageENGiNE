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
		Window(
			const std::string title = "NULL",
			int width = 1280,
			int height = 720,
			bool fullscreen = false
		);
		~Window();

		GLFWwindow * const getHandle() const;
		void setTitle(const std::string title);
		std::string getTitle() const;
		void setWidth(int width);
		int getWidth() const;
		void setHeight(int height);
		int getHeight() const;
	private:
		GLFWwindow * m_window;
		std::string m_title;
	};

}

#endif // WINDOW_H