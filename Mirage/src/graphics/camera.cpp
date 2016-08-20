#include "camera.h"

Camera::Camera(Transform t, glm::mat4 p, float e) :
	m_transform(t),
	m_projection(p),
	m_exposure(e)
{

}

void Camera::setTransform(const Transform &t)
{
	m_transform = t;
}

void Camera::setProjectionMatrix(const glm::mat4 &p)
{
	m_projection = p;
}

void Camera::setExposure(const float e)
{
	m_exposure = (m_exposure + e <= 1e-3f) ? m_exposure + e * 0.1f : m_exposure + e;
	m_exposure = (m_exposure + e * 0.1f <= 1e-3f) ? m_exposure + e * 0.01f : m_exposure + e * 0.1f;
}

glm::mat4 Camera::getViewMatrix()
{
	glm::mat4 t = glm::translate(m_transform.getPosition());
	glm::mat4 r = glm::mat4_cast(m_transform.getOrientation());

	return r * t;
}

const glm::mat4 & Camera::getProjectionMatrix() const
{
	return m_projection;
}

float Camera::getExposure() const
{
	return m_exposure;
}