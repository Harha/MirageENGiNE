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
		const std::string & identifier
	) :
		GameComponent(GC_FREEMOVE, identifier),
		m_sensitivity(sensitivity)
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

	void FreeLook::rotate(FreeLookDirection_t direction, float delta, float dt)
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
		}

		m_parent->getTransform().rotate(axis, delta * m_sensitivity * dt);
	}

	float FreeLook::setSensitivity(float sensitivity)
	{
		m_sensitivity = sensitivity;
	}

	float FreeLook::getSensitivity() const
	{
		return m_sensitivity;
	}

}