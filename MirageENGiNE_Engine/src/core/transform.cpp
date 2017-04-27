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
		m_parent(nullptr),
		m_position(position),
		m_orientation(orientation),
		m_scale(scale)
	{

	}

	Transform::Transform(
		Transform * const parent,
		glm::vec3 position,
		glm::quat orientation,
		glm::vec3 scale
	) :
		m_parent(parent),
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
		rotate(glm::angleAxis(glm::radians(angle), axis));
	}

	void Transform::rotate(const glm::quat & rotation)
	{
		m_orientation = glm::normalize(rotation * m_orientation);
	}

	void Transform::scale(const glm::vec3 & scale)
	{
		m_scale *= scale;
	}

	glm::mat4 Transform::getParentMatrix() const
	{
		if (m_parent != nullptr)
		{
			return m_parent->getModelMatrix();
		}

		return glm::mat4();
	}

	glm::mat4 Transform::getModelMatrix() const
	{
		glm::mat4 translation = glm::translate(m_position);
		glm::mat4 rotation = glm::mat4_cast(m_orientation);
		glm::mat4 scale = glm::scale(m_scale);

		return getParentMatrix() * translation * rotation * scale;
	}

	void Transform::setParent(Transform * const parent)
	{
		m_parent = parent;
	}

	Transform * const Transform::getParent() const
	{
		return m_parent;
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

	glm::vec3 Transform::getForward() const
	{
		return m_orientation * glm::vec3(0, 0, 1);
	}

	glm::vec3 Transform::getBackward() const
	{
		return m_orientation * glm::vec3(0, 0, -1);
	}

	glm::vec3 Transform::getLeft() const
	{
		return m_orientation * glm::vec3(-1, 0, 0);
	}

	glm::vec3 Transform::getRight() const
	{
		return m_orientation * glm::vec3(1, 0, 0);
	}

	glm::vec3 Transform::getUp() const
	{
		return m_orientation * glm::vec3(0, 1, 0);
	}

	glm::vec3 Transform::getDown() const
	{
		return m_orientation * glm::vec3(0, -1, 0);
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