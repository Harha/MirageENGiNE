#include "engine.h"

// VC++ Weirdness
#define NOMINMAX

// std includes
#include <iostream>
#include <thread>

// lib includes
#include <GLFW/glfw3.h>

// mirage includes
#include "config.h"
#include "macros.h"
#include "runstate.h"
#include "graphics/window.h"
#include "graphics/gfxengine.h"
#include "mesh.h"
#include "graphics/renderable_mesh.h"
#include "core/model_formats/wavefront_file.h"
#include "graphics/glsl/shader.h"

namespace mirage
{

	CoreEngine::CoreEngine(const std::string & cfgFilePath) :
		m_config(cfgFilePath),
		m_runState(ERS_UNINTIALIZED),
		m_window(nullptr),
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

		// Set engine run state to initialized
		m_runState = ERS_INITIALIZED;

		MLOG_INFO("CoreEngine::CoreEngine, initialized successfully. Config file path: %s", m_config.getFilePath().c_str());
	}

	CoreEngine::~CoreEngine()
	{
		MDELETES(m_window);
		MDELETES(m_graphicsEngine);
	}

	void CoreEngine::glfwKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{

	}

	void CoreEngine::run()
	{
		if (m_runState != ERS_INITIALIZED)
		{
			MLOG_WARNING("CoreEngine::run, engine was not initialized properly before this was called. Engine run state: %d", m_runState);
			return;
		}

		m_runState = ERS_RUNNING;

		try
		{
			ShaderProgram prog1("test", "", "basicmesh.vert.glsl", "basicmesh.frag.glsl");
		}
		catch (const std::exception & e)
		{
			MLOG_ERROR("Exception: %s", e.what());
		}

		MLOG_INFO("CoreEngine::run() called, entering main loop.");

		while (glfwWindowShouldClose(m_window->getHandle()) == GL_FALSE && m_runState == ERS_RUNNING)
		{
			// Poll for any glfw-related events
			glfwPollEvents();

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

	GraphicsEngine * const CoreEngine::getGraphicsEngine() const
	{
		return m_graphicsEngine;
	}

}