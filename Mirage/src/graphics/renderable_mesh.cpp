#include "renderable_mesh.h"

// lib includes
#include "../glad/glad.h"

// mirage includes
#include "../config.h"
#include "../macros.h"
#include "../core/mesh.h"
#include "vertex.h"

namespace mirage
{

	RenderableMesh::RenderableMesh(Mesh * mesh) :
		m_mesh(mesh)
	{
		MLOG_INFO("RenderableMesh::RenderableMesh initialized successfully. FilePath: %s", mesh->getFilePath().c_str());
	}

	void RenderableMesh::render()
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);

		glBindVertexArray(m_mesh->getData()->getVao());
		glBindBuffer(GL_ARRAY_BUFFER, m_mesh->getData()->getVbo());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, BUFFER_OFFSET(0));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, BUFFER_OFFSET(12));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, BUFFER_OFFSET(24));
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, BUFFER_OFFSET(36));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh->getData()->getIbo());
		glDrawElements(GL_TRIANGLES, m_mesh->getData()->getSize(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
	}

}