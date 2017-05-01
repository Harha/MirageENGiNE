#include "game.h"

// std includes
#include <cassert>

// lib includes
#include "3rdparty/imgui/imgui.h"
#include "3rdparty/imgui/imgui_impl_glfw_gl3.h"
#include "3rdparty/glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/gtx/string_cast.hpp>

// mirage includes
#include "config.h"
#include "macros.h"
#include "core/engine.h"
#include "core/transform.h"
#include "graphics/gfxengine.h"
#include "graphics/window.h"
#include "graphics/camera/camera.h"
#include "game/gobject.h"
#include "game/gcomponent.h"
#include "game/components/camera_perspective.h"
#include "game/components/model_basic.h"
#include "game/components/freemove.h"
#include "game/components/freelook.h"

namespace mirage
{

	Game::Game() :
		m_coreEngine(),
		m_objects()
	{
		// Create initial root game object
		GameObject * root = new GameObject("root", Transform());
		addRootLevelObject(root);

		MLOG_INFO("Game::Game, created.");
	}

	Game::~Game()
	{
		// Deallocate all game objects from memory
		clearAllObjects();

		MLOG_INFO("Game::~Game, destroyed.");
	}

	void Game::renderGUI_GameObjectTree(GameObject * const node)
	{
		if (node == nullptr)
		{
			throw std::exception("Game::renderGUI_GameObjectTree(node), error. Target node object is pointing to NULL!");
		}

		// Current game object text label
		std::string id_go("(object): " + node->getIdentifier());

		if (ImGui::TreeNode(id_go.c_str()))
		{
			// Render information about current game object
			if (ImGui::TreeNode("information: "))
			{
				ImGui::Text("Position: %s", glm::to_string(node->getTransform().getPosition()));
				ImGui::Text("Orientation: %s", glm::to_string(node->getTransform().getOrientation()));
				ImGui::Text("Scale: %s", glm::to_string(node->getTransform().getScale()));

				ImGui::TreePop();
			}

			for (auto child : node->getChildren())
			{
				renderGUI_GameObjectTree(child);
			}

			for (auto component : node->getComponents())
			{
				// Current component text label
				std::string id_gc("(component): " + component->getIdentifier());

				// Render extra information about each component type
				if (ImGui::TreeNode(id_gc.c_str()))
				{
					switch (component->getType())
					{
					case GC_GENERIC:
					{
						ImGui::Text("Type: GC_GENERIC");
					} break;
					case GC_CAMERA_PERSPECTIVE:
					{
						ImGui::Text("Type: GC_CAMERA_PERSPECTIVE");

						CameraPerspective * camera = static_cast<CameraPerspective *>(component);
						CameraPerspectiveSettings settings = camera->getSettings();

						ImGui::Text(
							"Fov: %.2f, aspect: %.2f, near: %.2f, far: %.2f, exposure: %.2f",
							settings.fov, settings.aspect, settings.nearplane, settings.farplane, camera->getCamera()->getExposure()
						);
					} break;
					case GC_CAMERA_ORTHOGRAPHIC:
					{
						ImGui::Text("Type: GC_CAMERA_ORTHOGRAPHIC");
					} break;
					case GC_MODEL_BASIC:
					{
						ImGui::Text("Type: GC_MODEL_BASIC");

						ModelBasic * model = static_cast<ModelBasic *>(component);

						ImGui::Text("File path: %s", model->getFilePath().c_str());
						ImGui::Text("Meshes: %zu", model->getMeshBases().size());
					} break;
					case GC_FREEMOVE:
					{
						ImGui::Text("Type: GC_FREEMOVE");

						FreeMove * freemove = static_cast<FreeMove *>(component);

						ImGui::Text("Speed: %.5f", freemove->getSpeed());
					} break;
					case GC_FREELOOK:
					{
						ImGui::Text("Type: GC_FREELOOK");

						FreeLook * freelook = static_cast<FreeLook *>(component);

						ImGui::Text("Sensitivity: %.5f, roll speed: %.5f", freelook->getSensitivity(), freelook->getRollSpeed());
					} break;
					}

					ImGui::TreePop();
				}
			}

			ImGui::TreePop();
		}
	}

	void Game::setEngine(CoreEngine * const engine)
	{
		m_coreEngine = engine;
	}

	CoreEngine * const Game::getEngine()
	{
		return m_coreEngine;
	}

	void Game::addRootLevelObject(GameObject * const object)
	{
		m_objects.push_back(object);
		object->setGame(this);
	}

	void Game::clearAllObjects()
	{
		for (auto object : m_objects)
		{
			MDELETES(object);
		}

		m_objects.clear();
	}

	const std::vector<GameObject *> & Game::getRootLevelObjects() const
	{
		return m_objects;
	}

	GameObject * const Game::getObject(const std::string & identifier, GameObject * const node)
	{
		if (node != nullptr)
		{
			// MLOG_DEBUG("getObject, node: %s", node->getIdentifier().c_str());

			if (node->getIdentifier() == identifier)
			{
				return node;
			}

			GameObject * found = nullptr;
			for (auto child : node->getChildren())
			{
				found = getObject(identifier, child);

				if (found != nullptr)
				{
					return found;
				}
			}
		}
		else
		{
			// MLOG_DEBUG("getObject, identifier: %s", identifier.c_str());

			GameObject * found = nullptr;
			for (auto object : m_objects)
			{
				found = getObject(identifier, object);

				if (found != nullptr)
				{
					return found;
				}
			}
		}

		return nullptr;
	}

	void Game::api_lockCursor(bool lock) const
	{
		glfwSetInputMode(m_coreEngine->getWindow()->getHandle(), GLFW_CURSOR, (lock == true) ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
	}

	bool Game::api_isCursorLocked() const
	{
		return (glfwGetInputMode(m_coreEngine->getWindow()->getHandle(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED) ? true : false;
	}

	void Game::api_setCursorPos(float x, float y)
	{
		glfwSetCursorPos(m_coreEngine->getWindow()->getHandle(), static_cast<double>(x), static_cast<double>(y));
	}

}