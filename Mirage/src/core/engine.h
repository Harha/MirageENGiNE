#ifndef ENGINE_H
#define ENGINE_H

// std includes
#include <string>

// mirage includes
#include "../config.h"
#include "../macros.h"
#include "../util/inifile.h"

// forward declarations
typedef struct GLFWwindow GLFWwindow;

namespace mirage
{

	// forward declarations
	enum EngineRunState;
	class Window;
	class GraphicsEngine;

	class CoreEngine
	{
	public:
		CoreEngine(const std::string & config = "./res/config.ini");
		~CoreEngine();
		void run();
		static void glfwKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
		const IniFile & getConfig() const;
		const EngineRunState & getRunState() const;
		Window * const getWindow() const;
		GraphicsEngine * const getGraphicsEngine() const;
	private:
		IniFile m_config;
		EngineRunState m_runState;
		Window * m_window;
		GraphicsEngine * m_graphicsEngine;
	};

}

#endif // ENGINE_H