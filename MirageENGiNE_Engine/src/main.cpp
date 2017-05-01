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
#include "game/game.h"

#include "test_game.h"

static void glfwErrorCallback(int error, const char * description)
{
	MLOG_ERROR("glfwErrorCallback, error: %d, description: %s", error, description);
}

int main(int argc, char * argv[])
{
	MLOG_INFO("MirageENGiNE, version %d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_BUGFIX);

	// Program runtime variables and objects
	int state = 0;
	mirage::CoreEngine * engine = nullptr;
	mirage::Game * game = nullptr;

	// Setup glfw error callback function
	glfwSetErrorCallback(glfwErrorCallback);

	try
	{
		// Initialize GLFW3
		if (glfwInit() == GL_FALSE)
		{
			throw std::exception("Failed to initialize GLFW3!");
		}

		// Create core engine instance
		engine = new mirage::CoreEngine("./data/config.ini");

		// Create test game instance & set it to current game
		game = new mirage::TestGame();
		engine->setGame(game);

		// Initialize glad
		if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == GL_FALSE)
		{
			glfwTerminate();
			throw std::exception("Failed to initialize glad!");
		}

		// Run the game engine logic
		engine->run();
	}
	catch (const std::exception & e)
	{
		// Set state to failure
		state = -1;

		// Log the exception type
		MLOG_ERROR("MirageENGiNE, exception: %s", e.what());
	}

	// After shutdown, cleanup resources
	MDELETES(engine);
	glfwTerminate();

	std::cin.get();

	return state;
}