#ifndef TRANSFORM_H
#define TRANSFORM_H

// lib includes
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
	Transform(glm::vec3 p = glm::vec3(0.0f), glm::quat o = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3 s = glm::vec3(1.0f, 1.0f, 1.0f));
	void translate(const glm::vec3 & dir, float l);
	void rotate(const glm::vec3 & axis, float theta);
	void rotate(const glm::quat & q);
	void scale(const glm::vec3 & scale);
	glm::mat4 getModelMatrix() const;
	void setPosition(const glm::vec3 &v);
	void setOrientation(const glm::quat &q);
	void setScale(const glm::vec3 &v);
	const glm::vec3 & getPosition() const;
	const glm::quat & getOrientation() const;
	const glm::vec3 & getScale() const;
private:
	glm::vec3 m_position;
	glm::quat m_orientation;
	glm::vec3 m_scale;
};

#endif // TRANSFORM_H