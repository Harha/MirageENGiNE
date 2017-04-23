#include "game.h"

// std includes
#include <cassert>

// lib includes
#include "3rdparty/imgui/imgui.h"
#include "3rdparty/imgui/imgui_impl_glfw_gl3.h"
#include "3rdparty/glad/glad.h"
#include <GLFW/glfw3.h>

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

namespace mirage
{

	Game::Game() :
		m_coreEngine(),
		m_objects()
	{
		// Create initial root game object
		GameObject * root = new GameObject("root", Transform(), nullptr, nullptr);
		addObject(root);

		MLOG_INFO("Game::Game, initialized.");
	}

	Game::~Game()
	{
		// Clear all game objects from memory
		clearObjects();

		MLOG_INFO("Game::~Game, destroyed. CoreEngine *: %p", (void *)m_coreEngine);
	}

	void Game::renderGUI_GameObjectTree(GameObject * const node)
	{
		if (node == nullptr)
			throw std::exception("Game::renderGUI_GameObjectTree(node), target node object is pointing to NULL!");

		std::string id_go("(object): " + node->getIdentifier());

		if (ImGui::TreeNode(id_go.c_str()))
		{
			for (auto child : node->getChildren())
			{
				renderGUI_GameObjectTree(child);
			}

			for (auto component : node->getComponents())
			{
				std::string id_gc("(component): " + component->getIdentifier());

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

	CoreEngine * Game::getEngine()
	{
		return m_coreEngine;
	}

	void Game::addObject(GameObject * const object)
	{
		m_objects.push_back(object);
		object->setGame(this);
	}

	void Game::clearObjects()
	{
		for (auto object : m_objects)
		{
			MDELETES(object);
		}

		m_objects.clear();
	}

	const std::vector<GameObject *> & Game::getObjects() const
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

		/*
		if (node != nullptr)
		{
			MLOG_DEBUG("getObject, node: %s", node->getIdentifier().c_str());

			if (node->getIdentifier() == identifier)
				return node;

			for (auto child : node->getChildren())
			{
				return getObject(identifier, child);
			}
		}
		else
		{
			MLOG_DEBUG("getObject, identifier: %s", identifier.c_str());

			for (auto object : m_objects)
			{
				return getObject(identifier, object);
			}
		}*/

		/*
		// If no target node specified, start from root level
		if (node == nullptr)
		{
			for (auto object : m_objects)
			{
				if (object->getIdentifier() == identifier)
					return object;

				return getObject(identifier, object);
			}

			// No objects to search, return NULL
			return nullptr;
		}
		else
		{
			MLOG_DEBUG("getObject, identifier: %s", node->getIdentifier().c_str());

			for (auto child : node->getChildren())
			{
				MLOG_DEBUG("getObject, child_identifier: %s", child->getIdentifier().c_str());

				if (child->getIdentifier() == identifier)
					return child;

				return getObject(identifier, child);
			}

			return nullptr;

			if (node->getIdentifier() == identifier)
				return node;

			for (auto child : node->getChildren())
			{
				if (child == nullptr)
					throw std::exception("GameObject::getObject(id, node), node child object is pointing to NULL!");

				return getObject(identifier, child);
			}

			// No childs to search, return NULL
			return nullptr;*/
	}

}