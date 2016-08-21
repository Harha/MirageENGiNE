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

		glErrorCheck();
		glfwSwapBuffers(m_coreEngine->getWindow()->getHandle());
	}

	void GraphicsEngine::glErrorCheck()
	{
		GLenum glError = glGetError();

		if (glError != GL_NO_ERROR)
		{
			std::string glErrorStr;
			switch (glError)
			{
			case GL_INVALID_OPERATION:
				glErrorStr = "GL_INVALID_OPERATION";
				break;
			case GL_INVALID_VALUE:
				glErrorStr = "GL_INVALID_VALUE";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				glErrorStr = "GL_INVALID_VALUE";
				break;
			case GL_OUT_OF_MEMORY:
				glErrorStr = "GL_INVALID_VALUE";
				break;
			default:
				glErrorStr = "GL_UNKNOWN_ERROR (";
				break;
			}

			MERR("glGetError(): " << glErrorStr);
		}
	}

}