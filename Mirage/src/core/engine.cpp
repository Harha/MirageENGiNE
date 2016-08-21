#include "engine.h"

// VC++ Weirdness
#define NOMINMAX

// std includes
#include <iostream>
#include <thread>

// lib includes
#include <GLFW/glfw3.h>

// mirage includes
#include "runstate.h"
#include "../graphics/window.h"
#include "../graphics/gfxengine.h"
#include "mesh.h"
#include "../graphics/renderable_mesh.h"
#include "model_formats/wavefront_file.h"

namespace mirage
{

	CoreEngine::CoreEngine(const std::string & configPath) :
		m_config(configPath),
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

		// Set window key callback function
		glfwSetKeyCallback(m_window->getHandle(), glfwKeyCallback);

		// Initialize graphics engine
		m_graphicsEngine = new GraphicsEngine(this);

		MLOG("CoreEngine::CoreEngine - Initialized successfully. Config file: " << m_config.getPath());
		m_runState = ERS_INITIALIZED;
	}

	CoreEngine::~CoreEngine()
	{
		MDELETES(m_window);
		MDELETES(m_graphicsEngine);
	}

	void CoreEngine::glfwKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		MLOG("Key pressed (key: " << key << ", scancode: " << scancode << ", action: " << action << ")");
	}

	void CoreEngine::run()
	{
		if (m_runState != ERS_INITIALIZED)
		{
			MWRN("CoreEngine Was not initialized properly before CoreEngine::run() was called. Initialization state: " << m_runState);
			return;
		}

		MLOG("CoreEngine::run() called, entering main loop.");
		m_runState = ERS_RUNNING;

		Mesh mesh1("sponza.obj");
		Mesh mesh2("sponza.obj");
		Mesh mesh3("sponza.obj");
		Mesh mesh4("sponza.obj");
		Mesh mesh5("sibenik.obj");

		RenderableMesh rmesh1(&mesh1);

		WavefrontFile wfFile1("./res/models/cornellbox_original.obj");

		while (glfwWindowShouldClose(m_window->getHandle()) == GL_FALSE || m_runState == ERS_RUNNING)
		{
			// Call glfw event callback functions
			glfwPollEvents();

			m_graphicsEngine->render();

			// Sleep for a bit, because why not?
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	const IniFile & CoreEngine::getConfig() const
	{
		return m_config;
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