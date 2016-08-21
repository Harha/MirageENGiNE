#ifndef CAMERA_H
#define CAMERA_H

// lib includes
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// mirage includes
#include "../core/transform.h"

namespace mirage
{

	class Camera
	{
	public:
		Camera(Transform t = Transform(), glm::mat4 p = glm::perspective(70.0f, 1.0f, 0.01f, 1028.0f), float e = 1.0f);
		void setTransform(const Transform &t);
		void setProjectionMatrix(const glm::mat4 &p);
		void setExposure(const float e);
		glm::mat4 getViewMatrix();
		const glm::mat4 & getProjectionMatrix() const;
		float getExposure() const;
	private:
		Transform m_transform;
		glm::mat4 m_projection;
		float m_exposure;
	};

}

#endif // CAMERA_H