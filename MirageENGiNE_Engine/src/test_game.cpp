#include "test_game.h"

// lib includes
#include "3rdparty/imgui/imgui.h"
#include "3rdparty/imgui/imgui_impl_glfw_gl3.h"
#include "3rdparty/glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/gtx/string_cast.hpp>

// mirage includes
#include "macros.h"
#include "core/engine.h"
#include "core/input.h"
#include "graphics/gfxengine.h"
#include "graphics/window.h"
#include "game/gobject.h"
#include "game/gcomponent.h"
#include "game/components/camera_perspective.h"
#include "game/components/model_basic.h"
#include "game/components/freemove.h"
#include "game/components/freelook.h"

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
		GameObject * player = new GameObject("player", Transform(glm::vec3(0, 0, 0)));
		CameraPerspective * camera_perspective = new CameraPerspective(
			70.0f,
			(float)m_coreEngine->getWindow()->getWidth() / (float)m_coreEngine->getWindow()->getHeight(),
			0.1f,
			1028.0f * 2.5f,
			1.0f
		);
		FreeMove * freemove = new FreeMove(0.2f);
		FreeLook * freelook = new FreeLook(0.025f, 0.25f);
		player->addComponent(camera_perspective);
		player->addComponent(freemove);
		player->addComponent(freelook);

		GameObject * lost_empire = new GameObject("lost_empire");
		ModelBasic * model_lost_empire = new ModelBasic(
			"lost_empire/lost_empire.obj",
			"model_lost_empire"
		);
		lost_empire->addComponent(model_lost_empire);

		// Add game objects to game
		GameObject * root = getObject("root");
		root->addChildren(player);
		root->addChildren(lost_empire);
	}

	void TestGame::update(float dt)
	{
		// Look around with freelook when mouse2 held down
		auto freelook = getObject("player")->getComponent<FreeLook *>("freelook");
		if (input::MS_BUTTONS[GLFW_MOUSE_BUTTON_2] == true)
		{
			// Calculate screen center position
			glm::vec2 center(
				static_cast<float>(m_coreEngine->getWindow()->getWidth() * 0.5f),
				static_cast<float>(m_coreEngine->getWindow()->getHeight() * 0.5f)
			);

			// Get mouse move amount
			glm::vec2 delta(
				input::MS_POS_X - center.x,
				input::MS_POS_Y - center.y
			);

			// Center mouse
			api_setCursorPos(center.x, center.y);

			// Do we rotate around x or y?
			bool rotate_x = delta.x > 0.0f || delta.x < 0.0f;
			bool rotate_y = delta.y > 0.0f || delta.y < 0.0f;

			// Rotate around x
			if (rotate_x)
			{
				freelook->look(FLD_X, -delta.x, dt);
			}

			// Rotate around y
			if (rotate_x)
			{
				freelook->look(FLD_Y, -delta.y, dt);
			}
		}

		if (input::KB_KEYS[GLFW_KEY_Q] != input::KBK_RELEASED)
		{
			freelook->look(FLD_Z, 1.0f, dt);
		}
		else if (input::KB_KEYS[GLFW_KEY_E] != input::KBK_RELEASED)
		{
			freelook->look(FLD_Z, -1.0f, dt);
		}

		// Player movement
		auto freemove = getObject("player")->getComponent<FreeMove *>("freemove");

		if (input::KB_KEYS[GLFW_KEY_W] != input::KBK_RELEASED)
		{
			freemove->move(FMD_FORWARD, dt);
		}
		else if (input::KB_KEYS[GLFW_KEY_S] != input::KBK_RELEASED)
		{
			freemove->move(FMD_BACKWARD, dt);
		}

		if (input::KB_KEYS[GLFW_KEY_A] != input::KBK_RELEASED)
		{
			freemove->move(FMD_LEFT, dt);
		}
		else if (input::KB_KEYS[GLFW_KEY_D] != input::KBK_RELEASED)
		{
			freemove->move(FMD_RIGHT, dt);
		}

		if (input::KB_KEYS[GLFW_KEY_R] != input::KBK_RELEASED)
		{
			freemove->move(FMD_UP, dt);
		}
		else if (input::KB_KEYS[GLFW_KEY_F] != input::KBK_RELEASED)
		{
			freemove->move(FMD_DOWN, dt);
		}

		//getObject("lost_empire")->getTransform().rotate(glm::vec3(0, 1, 0), 0.001f);
	}

	void TestGame::render(GraphicsEngine * const gfxEngine)
	{
		// Set current camera for scene
		gfxEngine->setCurrentCamera(getObject("player")->getComponent<CameraPerspective *>("camera_perspective")->getCamera());

		// Render models
		getObject("lost_empire")->render(gfxEngine);
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