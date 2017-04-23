#ifndef CAMERA_H
#define CAMERA_H

// lib includes
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// mirage includes
#include "core/transform.h"

namespace mirage
{

	class Camera
	{
	public:
		Camera(
			Transform * const transform = nullptr,
			glm::mat4 projection = glm::perspective(70.0f, 1.0f, 0.01f, 1028.0f),
			float exposure = 1.0f
		);
		~Camera();
		void setTransform(Transform * const transform);
		Transform * const getTransform() const;
		void setProjectionMatrix(const glm::mat4 & projection);
		const glm::mat4 & getProjectionMatrix() const;
		glm::mat4 getViewMatrix();
		void setExposure(const float exposure);
		float getExposure() const;
	private:
		Transform * m_transform;
		glm::mat4 m_projection;
		float m_exposure;
	};

}

#endif // CAMERA_H