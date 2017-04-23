// ----------------------------------------------------------------------------
// Mirage Game Engine
// Author: Harha
// (c) 2016-
// ----------------------------------------------------------------------------

 // VC++ Weirdness
#define NOMINMAX

 // std includes
#include <iostream>

// lib includes
#include "3rdparty/glad/glad.h"
#include <GLFW/glfw3.h>

// mirage includes
#include "config.h"
#include "macros.h"
#include "core/engine.h"

#include "test_game.h"

static void glfwErrorCallback(int error, const char * description)
{
	MLOG_ERROR("glfwErrorCallback, error: %d, description: %s", error, description);
}

int main(int argc, char * argv[])
{
	MLOG_INFO("Mirage Game Engine, version %d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_BUGFIX);

	// Set glfw error callback function
	glfwSetErrorCallback(glfwErrorCallback);

	// Initialize GLFW3
	if (glfwInit() == GL_FALSE)
	{
		return 1;
	}

	// Create core engine instance
	mirage::CoreEngine * engine = new mirage::CoreEngine("./data/config.ini");

	// Create test game instance
	mirage::TestGame * game = new mirage::TestGame();

	// Set engine game to our game instance
	engine->setGame(game);

	// Initialize glad, return error if failed
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == GL_FALSE)
	{
		MDELETES(game);
		MDELETES(engine);
		glfwTerminate();
		return 1;
	}

	// Go into program main loop, exit on CoreEngine::~CoreEngine()
	engine->run();

	// Cleanup resources
	MDELETES(engine);
	glfwTerminate();

	return 0;
}