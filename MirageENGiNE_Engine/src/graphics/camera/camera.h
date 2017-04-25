#ifndef CAMERA_H
#define CAMERA_H

// lib includes
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace mirage
{

	class Transform;

	class Camera
	{
	public:
		Camera(
			Transform * const transform,
			glm::mat4 projection,
			float exposure
		);
		~Camera();

		void setTransform(Transform * const transform);
		Transform * const getTransform() const;
		void setProjectionMatrix(const glm::mat4 & projection);
		const glm::mat4 & getProjectionMatrix() const;
		glm::mat4 getViewMatrix();
		void setExposure(float exposure);
		float getExposure() const;
	private:
		Transform * m_transform;
		glm::mat4 m_projection;
		float m_exposure;
	};

}

#endif // CAMERA_H