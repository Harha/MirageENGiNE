#include "freelook.h"

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

	FreeLook::FreeLook(
		float sensitivity,
		float rollSpeed,
		const std::string & identifier
	) :
		GameComponent(GC_FREEMOVE, identifier),
		m_sensitivity(sensitivity),
		m_rollSpeed(rollSpeed)
	{

	}

	FreeLook::~FreeLook()
	{

	}

	void FreeLook::update(float dt)
	{

	}

	void FreeLook::render(GraphicsEngine * const gfxEngine)
	{

	}

	void FreeLook::look(FreeLookDirection_t direction, float delta, float dt)
	{
		glm::vec3 axis(0.0f);

		switch (direction)
		{
		case FLD_X:
			axis = m_parent->getTransform().getUp();
			break;
		case FLD_Y:
			axis = m_parent->getTransform().getRight();
			break;
		case FLD_Z:
			axis = m_parent->getTransform().getForward();
			break;
		}

		m_parent->getTransform().rotate(axis, delta * ((direction != FLD_Z) ? m_sensitivity : m_rollSpeed) * dt);
	}

	void FreeLook::setSensitivity(float sensitivity)
	{
		m_sensitivity = sensitivity;
	}

	float FreeLook::getSensitivity() const
	{
		return m_sensitivity;
	}

	void FreeLook::setRollSpeed(float rollSpeed)
	{
		m_rollSpeed = rollSpeed;
	}

	float FreeLook::getRollSpeed() const
	{
		return m_rollSpeed;
	}

}