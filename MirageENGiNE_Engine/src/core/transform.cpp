#include "transform.h"

// lib includes
#include <glm/gtx/transform.hpp>

// mirage includes
#include "macros.h"

namespace mirage
{

	Transform::Transform(
		glm::vec3 position,
		glm::quat orientation,
		glm::vec3 scale
	) :
		m_position(position),
		m_orientation(orientation),
		m_scale(scale)
	{

	}

	void Transform::translate(const glm::vec3 & direction, float t)
	{
		m_position += direction * t;
	}

	void Transform::rotate(const glm::vec3 & axis, float angle)
	{
		rotate(glm::angleAxis(angle, axis));
	}

	void Transform::rotate(const glm::quat & rotation)
	{
		m_orientation = glm::normalize(rotation * m_orientation);
	}

	void Transform::scale(const glm::vec3 & scale)
	{
		m_scale *= scale;
	}

	glm::mat4 Transform::getModelMatrix() const
	{
		glm::mat4 translation = glm::translate(m_position);
		glm::mat4 rotation = glm::mat4_cast(m_orientation);
		glm::mat4 scale = glm::scale(m_scale);

		return translation * rotation * scale;
	}

	void Transform::setPosition(const glm::vec3 & position)
	{
		m_position = position;
	}

	const glm::vec3 & Transform::getPosition() const
	{
		return m_position;
	}

	void Transform::setOrientation(const glm::quat & orientation)
	{
		m_orientation = orientation;
	}

	const glm::quat & Transform::getOrientation() const
	{
		return m_orientation;
	}

	void Transform::setScale(const glm::vec3 & scale)
	{
		m_scale = scale;
	}

	const glm::vec3 & Transform::getScale() const
	{
		return m_scale;
	}

}