#include "camera.h"

// mirage includes
#include "macros.h"
#include "core/transform.h"

namespace mirage
{

	Camera::Camera(
		Transform * const transform,
		glm::mat4 projection,
		float exposure
	) :
		m_transform(transform),
		m_projection(projection),
		m_exposure(exposure)
	{
		MLOG_DEBUG("Camera::Camera, created. Exposure: %.2f", m_exposure);
	}

	Camera::~Camera()
	{
		MLOG_DEBUG("Camera::~Camera, destroyed.");
	}

	void Camera::setTransform(Transform * const transform)
	{
		m_transform = transform;
	}

	Transform * const Camera::getTransform() const
	{
		return m_transform;
	}

	void Camera::setProjectionMatrix(const glm::mat4 & projection)
	{
		m_projection = projection;
	}

	const glm::mat4 & Camera::getProjectionMatrix() const
	{
		return m_projection;
	}

	glm::mat4 Camera::getViewMatrix()
	{
		glm::mat4 translation = glm::translate(m_transform->getPosition() * glm::vec3(-1.0f));
		glm::mat4 rotation = glm::mat4_cast(glm::conjugate(m_transform->getOrientation()));

		return rotation * translation;
	}

	void Camera::setExposure(float exposure)
	{
		m_exposure = (m_exposure + exposure <= 1e-3f) ? m_exposure + exposure * 0.1f : m_exposure + exposure;
		m_exposure = (m_exposure + exposure * 0.1f <= 1e-3f) ? m_exposure + exposure * 0.01f : m_exposure + exposure * 0.1f;
	}

	float Camera::getExposure() const
	{
		return m_exposure;
	}

}