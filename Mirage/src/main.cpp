/*
 * Mirage Game Engine
 * Author: Harha
 * (c) 2016-
 */

 // VC++ Weirdness
#define NOMINMAX

 // std includes
#include <iostream>

// lib includes
#include "glad/glad.h"
#include <GLFW/glfw3.h>

// mirage includes
#include "config.h"
#include "macros.h"
#include "core/engine.h"
#include "graphics/window.h"

static void glfwErrorCallback(int error, const char * description)
{
	MERR(description);
}

int main(int argc, char * argv[])
{
	MLOG("Mirage Game Engine, version " << VERSION_STATE << "." << VERSION_MAJOR << "." << VERSION_MINOR);

	// Set glfw error callback function
	glfwSetErrorCallback(glfwErrorCallback);

	// Initialize GLFW3
	if (glfwInit() == GL_FALSE)
	{
		return 1;
	}

	// Create core engine instance
	mirage::CoreEngine * engine = new mirage::CoreEngine("./res/config.ini");

	// Initialize glad, return error if failed
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == GL_FALSE)
	{
		MDELETES(engine);
		glfwTerminate();
		return 1;
	}

	// Go into program main loop, exit on CoreEngine::~CoreEngine()
	engine->run();

	// Cleanup resources in correct order
	MDELETES(engine);
	glfwTerminate();

	return 0;
}