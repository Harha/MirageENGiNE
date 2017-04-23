#include "vertex.h"

// mirage includes
#include "macros.h"

namespace mirage
{

	const int Vertex::SIZE = 11;

	Vertex::Vertex(
		glm::vec3 position,
		glm::vec3 normal,
		glm::vec3 tangent,
		glm::vec2 uv
	) :
		m_position(position),
		m_normal(normal),
		m_tangent(tangent),
		m_uv(uv)
	{

	}

	const glm::vec3 & Vertex::getPosition() const
	{
		return m_position;
	}

	const glm::vec3 & Vertex::getNormal() const
	{
		return m_normal;
	}

	const glm::vec3 & Vertex::getTangent() const
	{
		return m_tangent;
	}

	const glm::vec2 & Vertex::getUV() const
	{
		return m_uv;
	}

}