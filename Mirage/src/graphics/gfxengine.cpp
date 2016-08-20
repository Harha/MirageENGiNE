#include "gfxengine.h"

// VC++ Weirdness
#define NOMINMAX

// std includes
#include <iostream>

// lib includes
#include "../glad/glad.h"
#include <GLFW/glfw3.h>

// mirage includes
#include "../core/runstate.h"
#include "../core/engine.h"
#include "window.h"

namespace mirage
{

	GraphicsEngine::GraphicsEngine(CoreEngine * const coreEngine) :
		m_runState(ERS_UNINTIALIZED),
		m_coreEngine(coreEngine)
	{

		MLOG("GraphicsEngine: Initialized successfully.");
		m_runState = ERS_INITIALIZED;
	}

	GraphicsEngine::~GraphicsEngine()
	{
	}

	void GraphicsEngine::render()
	{
		glClearColor(0.33f, 0.33f, 0.33f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_coreEngine->getWindow()->getHandle());
	}

}