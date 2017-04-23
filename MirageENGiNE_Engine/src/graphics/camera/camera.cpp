#include "camera.h"

// mirage includes
#include "macros.h"

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
		MLOG_DEBUG("Camera::Camera, created.");
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
		glm::mat4 t = glm::translate(m_transform->getPosition());
		glm::mat4 r = glm::mat4_cast(m_transform->getOrientation());

		return r * t;
	}

	void Camera::setExposure(const float exposure)
	{
		m_exposure = (m_exposure + exposure <= 1e-3f) ? m_exposure + exposure * 0.1f : m_exposure + exposure;
		m_exposure = (m_exposure + exposure * 0.1f <= 1e-3f) ? m_exposure + exposure * 0.01f : m_exposure + exposure * 0.1f;
	}

	float Camera::getExposure() const
	{
		return m_exposure;
	}

}