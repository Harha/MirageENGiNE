#ifndef ENGINE_H
#define ENGINE_H

// std includes
#include <string>

// mirage includes
#include "core/runstate.h"
#include "util/inifile.h"

typedef struct GLFWwindow GLFWwindow;

namespace mirage
{

	class Window;
	class GraphicsEngine;
	class Game;

	class CoreEngine
	{
	public:
		CoreEngine(
			const std::string & cfgFilePath = "./data/config.ini"
		);
		~CoreEngine();

		static void glfwWindowSizeCallback(GLFWwindow * window, int width, int height);
		static void glfwKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
		static void glfwMouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
		static void glfwCursorPosCallback(GLFWwindow * window, double x, double y);

		void run();
		const IniFile & getConfig() const;
		const EngineRunState & getRunState() const;
		Window * const getWindow() const;
		GraphicsEngine * const getGraphicsEngine() const;
		void setGame(Game * const game);
		Game * const getGame() const;
	private:
		IniFile m_config;
		EngineRunState m_runState;
		Window * m_window;
		GraphicsEngine * m_graphicsEngine;
		Game * m_game;
	};

}

#endif // ENGINE_H