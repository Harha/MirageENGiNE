#ifndef GOBJECT_H
#define GOBJECT_H

// std includes
#include <string>
#include <vector>

// mirage includes
#include "core/transform.h"

namespace mirage
{

	class GraphicsEngine;
	class Game;
	class GameComponent;

	class GameObject
	{
	public:
		GameObject(
			const std::string & identifier = "GameObject",
			Transform transform = Transform()
		);
		~GameObject();

		void update(float dt);
		void render(GraphicsEngine * const gfxEngine);
		void setIdentifier(const std::string & identifier);
		const std::string & getIdentifier() const;
		void setTransform(const Transform & transform);
		Transform & getTransform();
		void setGame(Game * const game);
		Game * const getGame() const;
		void setParent(GameObject * const parent);
		GameObject * const getParent() const;
		void addChildren(GameObject * const child);
		const std::vector<GameObject *> & getChildren() const;
		void addComponent(GameComponent * const component);
		const std::vector<GameComponent *> & getComponents() const;
		template<typename T> T const getComponent(const std::string & identifier)
		{
			for (auto component : m_components)
			{
				if (component->getIdentifier() == identifier)
					return static_cast<T>(component);
			}

			return nullptr;
		}
	private:
	protected:
		std::string m_identifier;
		Transform m_transform;
		Game * m_game;
		GameObject * m_parent;
		std::vector<GameObject *> m_children;
		std::vector<GameComponent *> m_components;
	};

}

#endif // GOBJECT_H