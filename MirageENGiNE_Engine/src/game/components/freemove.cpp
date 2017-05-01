#include "freemove.h"

// lib includes
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// mirage includes
#include "macros.h"
#include "graphics/gfxengine.h"
#include "game/gobject.h"
#include "core/transform.h"

namespace mirage
{

	FreeMove::FreeMove(
		float speed,
		const std::string & identifier
	) :
		GameComponent(GC_FREEMOVE, identifier),
		m_speed(speed)
	{

	}

	FreeMove::~FreeMove()
	{

	}

	void FreeMove::update(float dt)
	{

	}

	void FreeMove::render(GraphicsEngine * const gfxEngine)
	{

	}

	void FreeMove::move(FreeMoveDirection_t direction, float dt)
	{
		glm::vec3 direction_v(0.0f);

		switch (direction)
		{
		case FMD_FORWARD:
			direction_v = m_parent->getTransform().getForward();
			break;
		case FMD_BACKWARD:
			direction_v = m_parent->getTransform().getBackward();
			break;
		case FMD_LEFT:
			direction_v = m_parent->getTransform().getLeft();
			break;
		case FMD_RIGHT:
			direction_v = m_parent->getTransform().getRight();
			break;
		case FMD_UP:
			direction_v = m_parent->getTransform().getUp();
			break;
		case FMD_DOWN:
			direction_v = m_parent->getTransform().getDown();
			break;
		}

		m_parent->getTransform().translate(direction_v, m_speed * dt);
	}

	void FreeMove::setSpeed(float speed)
	{
		m_speed = speed;
	}

	float FreeMove::getSpeed() const
	{
		return m_speed;
	}

}