#include "transform.h"

// lib includes
#include <glm/gtx/transform.hpp>

// mirage includes
#include "../macros.h"

namespace mirage
{

	Transform::Transform(glm::vec3 p, glm::quat o, glm::vec3 s) :
		m_position(p),
		m_orientation(o),
		m_scale(s)
	{

	}

	void Transform::translate(const glm::vec3 & dir, float l)
	{
		m_position += dir * l;
	}

	void Transform::rotate(const glm::vec3 & axis, float theta)
	{
		rotate(glm::angleAxis(theta, axis));
	}

	void Transform::rotate(const glm::quat & q)
	{
		m_orientation = glm::normalize(q * m_orientation);
	}

	void Transform::scale(const glm::vec3 & scale)
	{
		m_scale *= scale;
	}

	glm::mat4 Transform::getModelMatrix() const
	{
		glm::mat4 t = glm::translate(m_position);
		glm::mat4 r = glm::mat4_cast(m_orientation);
		glm::mat4 s = glm::scale(m_scale);

		return t * r * s;
	}

	void Transform::setPosition(const glm::vec3 &v)
	{
		m_position = v;
	}

	void Transform::setOrientation(const glm::quat &q)
	{
		m_orientation = q;
	}

	void Transform::setScale(const glm::vec3 &v)
	{
		m_scale = v;
	}

	const glm::vec3 & Transform::getPosition() const
	{
		return m_position;
	}

	const glm::quat & Transform::getOrientation() const
	{
		return m_orientation;
	}

	const glm::vec3 & Transform::getScale() const
	{
		return m_scale;
	}

}