#include "engine.h"

// VC++ Weirdness
#define NOMINMAX

// std includes
#include <iostream>
#include <thread>
#include <chrono>

// lib includes
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// mirage includes
#include "config.h"
#include "macros.h"
#include "runstate.h"
#include "graphics/window.h"
#include "graphics/gfxengine.h"
#include "game/game.h"

namespace mirage
{

	CoreEngine::CoreEngine(
		const std::string & cfgFilePath,
		Game * const game
	) :
		m_config(cfgFilePath),
		m_runState(ERS_UNINTIALIZED),
		m_window(nullptr),
		m_game(game),
		m_graphicsEngine(nullptr)
	{
		// Initialize window
		m_window = new Window(
			m_config.getString("[gfx]", "windowT", "Mirage Game Engine"),
			m_config.getInt("[gfx]", "windowW", 1280),
			m_config.getInt("[gfx]", "windowH", 720),
			m_config.getBool("[gfx]", "fullscreen", false)
		);

		// Set glfw window key callback function
		glfwSetKeyCallback(m_window->getHandle(), glfwKeyCallback);

		// Initialize graphics engine
		m_graphicsEngine = new GraphicsEngine(this);

		// Initialize game
		setGame(game);

		// Set engine run state to initialized
		m_runState = ERS_INITIALIZED;

		MLOG_INFO("CoreEngine::CoreEngine, initialized. Config file path: %s", m_config.getFilePath().c_str());
	}

	CoreEngine::~CoreEngine()
	{
		MDELETES(m_game);
		MDELETES(m_graphicsEngine);
		MDELETES(m_window);

		MLOG_INFO("CoreEngine::~CoreEngine, destroyed.");
	}

	void CoreEngine::glfwKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		MLOG_DEBUG("CoreEngine::glfwKeyCallback, key: %d, scancode: %d, action: %d, mods: %d", key, scancode, action, mods);
	}

	void CoreEngine::run()
	{
		MLOG_INFO("CoreEngine::run() called, initializing and entering main loop...");

		if (m_runState != ERS_INITIALIZED)
		{
			MLOG_WARNING("CoreEngine::run, engine was not initialized properly before this was called. Engine run state: %d", m_runState);
			return;
		}

		// Initialize graphics engine
		m_graphicsEngine->initialize();

		// Initialize game
		m_game->initialize();

		m_runState = ERS_RUNNING;
		while (glfwWindowShouldClose(m_window->getHandle()) == GL_FALSE && m_runState == ERS_RUNNING)
		{
			// Poll for any glfw-related events
			glfwPollEvents();

			// Update / Render game & execute all rendering tasks in graphicsEngine
			m_game->update(1.0f);
			m_game->render(m_graphicsEngine);
			m_graphicsEngine->render();

			// Sleep for a bit, because why not?
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		MLOG_INFO("CoreEngine::run, exiting main loop. Engine run state: %d", m_runState);
	}

	const IniFile & CoreEngine::getConfig() const
	{
		return m_config;
	}

	const EngineRunState & CoreEngine::getRunState() const
	{
		return m_runState;
	}

	Window * const CoreEngine::getWindow() const
	{
		return m_window;
	}

	void CoreEngine::setGame(Game * const game)
	{
		if (game != nullptr)
		{
			m_game = game;
			m_game->setEngine(this);
		}

		MLOG_DEBUG("Game::setGame, called. Game *: %p", (void *)game);
	}

	Game * const CoreEngine::getGame() const
	{
		return m_game;
	}

	GraphicsEngine * const CoreEngine::getGraphicsEngine() const
	{
		return m_graphicsEngine;
	}

}