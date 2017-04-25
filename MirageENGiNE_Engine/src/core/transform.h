#ifndef TRANSFORM_H
#define TRANSFORM_H

// lib includes
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace mirage
{

	class Transform
	{
	public:
		Transform(
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3 sscale = glm::vec3(1.0f, 1.0f, 1.0f)
		);
		Transform(
			Transform * const parent,
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3 sscale = glm::vec3(1.0f, 1.0f, 1.0f)
		);

		void translate(const glm::vec3 & direction, float t);
		void rotate(const glm::vec3 & axis, float angle);
		void rotate(const glm::quat & rotation);
		void scale(const glm::vec3 & scale);
		glm::mat4 getParentMatrix() const;
		glm::mat4 getModelMatrix() const;
		void setParent(Transform * const parent);
		Transform * const getParent() const;
		void setPosition(const glm::vec3 & position);
		const glm::vec3 & getPosition() const;
		void setOrientation(const glm::quat & orientation);
		const glm::quat & getOrientation() const;
		void setScale(const glm::vec3 & scale);
		const glm::vec3 & getScale() const;
	private:
		Transform * m_parent;
		glm::vec3 m_position;
		glm::quat m_orientation;
		glm::vec3 m_scale;
	};

}

#endif // TRANSFORM_H