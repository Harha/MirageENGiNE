#include "gcomponent.h"

// mirage includes
#include "macros.h"
#include "graphics/gfxengine.h"
#include "game/gobject.h"

namespace mirage
{

	GameComponent::GameComponent(
		GameComponent_t type,
		const std::string & identifier
	) :
		m_type(type),
		m_identifier(identifier),
		m_parent(nullptr)
	{
		MLOG_DEBUG("GameComponent::GameComponent, created. Type: %u, identifier: %s", m_type, m_identifier.c_str());
	}

	GameComponent::~GameComponent()
	{
		MLOG_DEBUG("GameComponent::~GameComponent, destroyed. Identifier: %s", m_identifier.c_str());
	}

	GameComponent_t GameComponent::getType() const
	{
		return m_type;
	}

	void GameComponent::setIdentifier(const std::string & identifier)
	{
		m_identifier = identifier;
	}

	const std::string & GameComponent::getIdentifier() const
	{
		return m_identifier;
	}

	void GameComponent::setParent(GameObject * const parent)
	{
		m_parent = parent;
	}

	GameObject * const GameComponent::getParent() const
	{
		return m_parent;
	}

}