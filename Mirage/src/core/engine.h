#ifndef ENGINE_H
#define ENGINE_H

// std includes
#include <string>

// mirage includes
#include "util/inifile.h"

typedef struct GLFWwindow GLFWwindow;

namespace mirage
{

	enum EngineRunState;
	class Window;
	class GraphicsEngine;
	class Game;

	class CoreEngine
	{
	public:
		CoreEngine(
			const std::string & cfgFilePath = "./data/config.ini",
			Game * const game = nullptr
		);
		~CoreEngine();

		static void glfwKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);

		void run();
		const IniFile & getConfig() const;
		const EngineRunState & getRunState() const;
		Window * const getWindow() const;
		void setGame(Game * const game);
		Game * const getGame() const;
		GraphicsEngine * const getGraphicsEngine() const;
	private:
		IniFile m_config;
		EngineRunState m_runState;
		Window * m_window;
		Game * m_game;
		GraphicsEngine * m_graphicsEngine;
	};

}

#endif // ENGINE_H