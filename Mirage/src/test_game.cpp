#include "test_game.h"

// lib includes
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "glad/glad.h"
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
		GameObject * player_freelook = new GameObject("player_freelook", Transform(glm::vec3(0, 0, -5)), nullptr, nullptr);
		getObject("root")->addChildren(player_freelook);
		CameraPerspective * camera_perspective = new CameraPerspective(
			"camera_perspective",
			70.0f,
			(float)m_coreEngine->getWindow()->getWidth() / (float)m_coreEngine->getWindow()->getHeight(),
			0.01f,
			1028.0f,
			1.0f
		);
		getObject("player_freelook")->addComponent(camera_perspective);

		GameObject * player_fps = new GameObject("player_fps", Transform(), nullptr, nullptr);
		getObject("root")->addChildren(player_fps);

		GameObject * model_test = new GameObject("model_test", Transform(), nullptr, nullptr);
		getObject("root")->addChildren(model_test);
		ModelBasic * model_basic = new ModelBasic(
			"mitsuba/mitsuba.obj",
			"mitsuba_testmodel"
		);
		model_test->addComponent(model_basic);
	}

	void TestGame::update(float dt)
	{
		getObject("model_test")->getTransform().rotate(glm::vec3(0, 1, 0), 0.0025f);
	}

	void TestGame::render(GraphicsEngine * const gfxEngine)
	{
		gfxEngine->setCurrentCamera(getObject("player_freelook")->getComponent<CameraPerspective *>("camera_perspective")->getCamera());

		getObject("model_test")->render(gfxEngine);
	}

	void TestGame::renderGUI()
	{
		ImGui_ImplGlfwGL3_NewFrame();

		// Render Game Object node tree
		ImGui::Begin("Game Object tree");
		renderGUI_GameObjectTree(getObject("root"));
		ImGui::End();

		ImGui::Render();
	}



}