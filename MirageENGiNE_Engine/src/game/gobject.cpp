#include "gobject.h"

// mirage includes
#include "macros.h"
#include "graphics/gfxengine.h"
#include "game/game.h"
#include "game/gcomponent.h"

namespace mirage
{

	GameObject::GameObject(
		const std::string & identifier,
		Transform transform
	) :
		m_identifier(identifier),
		m_transform(transform),
		m_game(nullptr),
		m_parent(nullptr),
		m_children(),
		m_components()
	{
		MLOG_DEBUG("GameObject::GameObject, created. Identifier: %s", m_identifier.c_str());
	}

	GameObject::~GameObject()
	{
		// Clear all components from memory
		for (auto component : m_components)
		{
			MDELETES(component);
		}

		// Clear all child objects from memory
		for (auto child : m_children)
		{
			MDELETES(child);
		}

		MLOG_DEBUG("GameObject::~GameObject, destroyed. Identifier: %s", m_identifier.c_str());
	}

	void GameObject::update(float dt)
	{
		for (auto component : m_components)
		{
			component->update(dt);
		}

		for (auto child : m_children)
		{
			child->update(dt);
		}
	}

	void GameObject::render(GraphicsEngine * const gfxEngine)
	{
		for (auto component : m_components)
		{
			component->render(gfxEngine);
		}

		for (auto child : m_children)
		{
			child->render(gfxEngine);
		}
	}

	void GameObject::setIdentifier(const std::string & identifier)
	{
		m_identifier = identifier;
	}

	const std::string & GameObject::getIdentifier() const
	{
		return m_identifier;
	}

	void GameObject::setTransform(const Transform & transform)
	{
		m_transform = transform;
	}

	Transform & GameObject::getTransform()
	{
		return m_transform;
	}

	void GameObject::setGame(Game * const game)
	{
		m_game = game;
	}

	Game * const GameObject::getGame() const
	{
		return m_game;
	}

	void GameObject::setParent(GameObject * const parent)
	{
		m_parent = parent;
		m_game = parent->getGame();
		m_transform.setParent(&parent->getTransform());
	}

	GameObject * const GameObject::getParent() const
	{
		return m_parent;
	}

	void GameObject::addChildren(GameObject * const child)
	{
		m_children.push_back(child);
		child->setParent(this);
	}

	const std::vector<GameObject *> & GameObject::getChildren() const
	{
		return m_children;
	}

	void GameObject::addComponent(GameComponent * const component)
	{
		m_components.push_back(component);
		component->setParent(this);
	}

	const std::vector<GameComponent *> & GameObject::getComponents() const
	{
		return m_components;
	}

}