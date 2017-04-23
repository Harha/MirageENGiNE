#include "vertex.h"

// mirage includes
#include "macros.h"

namespace mirage
{

	const int Vertex::SIZE = 11;

	Vertex::Vertex(glm::vec3 p, glm::vec3 n, glm::vec3 t, glm::vec2 uv) :
		m_position(p),
		m_normal(n),
		m_tangent(t),
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