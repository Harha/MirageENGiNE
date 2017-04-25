#include "test_game.h"

// lib includes
#include "3rdparty/imgui/imgui.h"
#include "3rdparty/imgui/imgui_impl_glfw_gl3.h"
#include "3rdparty/glad/glad.h"
#include <GLFW/glfw3.h>

// mirage includes
#include "macros.h"
#include "core/engine.h"
#include "graphics/gfxengine.h"
#include "graphics/window.h"
#include "game/gobject.h"
#include "game/gcomponent.h"
#include "game/components/camera_perspective.h"
#include "game/components/model_basic.h"

namespace mirage
{

	TestGame::TestGame() :
		Game()
	{

	}

	TestGame::~TestGame()
	{

	}

	void TestGame::initialize()
	{
		// Create game objects
		GameObject * player = new GameObject("player", Transform(glm::vec3(0, -2, -10)));
		CameraPerspective * camera_perspective = new CameraPerspective(
			"camera_perspective",
			70.0f,
			(float)m_coreEngine->getWindow()->getWidth() / (float)m_coreEngine->getWindow()->getHeight(),
			0.01f,
			1028.0f,
			1.0f
		);
		player->addComponent(camera_perspective);

		GameObject * mitsuba = new GameObject("mitsuba");
		ModelBasic * model_mitsuba = new ModelBasic(
			"mitsuba/mitsuba.obj",
			"model_mitsuba"
		);
		mitsuba->addComponent(model_mitsuba);

		// Add game objects to game
		GameObject * root = getObject("root");
		root->addChildren(player);
		root->addChildren(mitsuba);
	}

	void TestGame::update(float dt)
	{
		getObject("mitsuba")->getTransform().rotate(glm::vec3(0, 1, 0), 0.001f);
	}

	void TestGame::render(GraphicsEngine * const gfxEngine)
	{
		// Set current camera for scene
		gfxEngine->setCurrentCamera(getObject("player")->getComponent<CameraPerspective *>("camera_perspective")->getCamera());

		// Render models
		getObject("mitsuba")->render(gfxEngine);
	}

	void TestGame::renderGUI()
	{
		ImGui_ImplGlfwGL3_NewFrame();

		// Render GameObject node tree
		ImGui::Begin("GameObject tree");
		renderGUI_GameObjectTree(getObject("root"));
		ImGui::End();

		ImGui::Render();
	}



}