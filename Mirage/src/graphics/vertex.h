#ifndef VERTEX_H
#define VERTEX_H

// lib includes
#include <glm/glm.hpp>

namespace mirage
{

	class Vertex
	{
	public:
		static const int SIZE;

		Vertex(glm::vec3 p = glm::vec3(0.0f), glm::vec3 n = glm::vec3(0.0f), glm::vec3 t = glm::vec3(0.0f), glm::vec2 uv = glm::vec2(0.0f));
		const glm::vec3 & getPosition() const;
		const glm::vec3 & getNormal() const;
		const glm::vec3 & getTangent() const;
		const glm::vec2 & getUV() const;
	private:
		glm::vec3 m_position;
		glm::vec3 m_normal;
		glm::vec3 m_tangent;
		glm::vec2 m_uv;
	};

}

#endif // VERTEX_H