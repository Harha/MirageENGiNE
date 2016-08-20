#ifndef WINDOW_H
#define WINDOW_H

// std includes
#include <string>

// forward declarations
typedef struct GLFWwindow GLFWwindow;

class Window
{
public:
	Window(const std::string t = "window", int w = 1280, int h = 720, bool fs = false);
	~Window();

	void setTitle(const std::string t);
	int getWidth() const;
	int getHeight() const;
	GLFWwindow * const getHandle() const;
private:
	GLFWwindow * m_window;
};

#endif // WINDOW_H