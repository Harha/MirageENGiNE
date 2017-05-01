#include "mesh_renderer.h"

// lib includes
#include "3rdparty/glad/glad.h"

// mirage includes
#include "config.h"
#include "macros.h"
#include "core/vertex.h"
#include "core/transform.h"
#include "core/mesh/mesh_base.h"

namespace mirage
{

	// ---------------------------------------------------------------------------
	// MeshRendererData
	// ---------------------------------------------------------------------------

	MeshRendererData::MeshRendererData() :
		m_vao(0),
		m_vbo(0),
		m_ibo(0),
		m_refAmount(0)
	{
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);

		MLOG_DEBUG("MeshRendererData::MeshRendererData, created. VAO: %d, VBO: %d, IBO: %d", m_vao, m_vbo, m_ibo);
	}

	MeshRendererData::~MeshRendererData()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ibo);

		MLOG_DEBUG("MeshRendererData::~MeshRendererData, destroyed.");
	}

	const GLuint MeshRendererData::getVao() const
	{
		return m_vao;
	}

	const GLuint MeshRendererData::getVbo() const
	{
		return m_vbo;
	}

	const GLuint MeshRendererData::getIbo() const
	{
		return m_ibo;
	}

	void MeshRendererData::addReference()
	{
		m_refAmount++;
	}

	void MeshRendererData::delReference()
	{
		m_refAmount = (m_refAmount - 1 < 0) ? 0 : m_refAmount - 1;
	}

	const int32_t MeshRendererData::getRefAmount() const
	{
		return m_refAmount;
	}

	// ---------------------------------------------------------------------------
	// MeshRenderer
	// ---------------------------------------------------------------------------

	std::map<std::string, MeshRendererData *> LOADED_MESH_RENDERERS;

	MeshRenderer::MeshRenderer(MeshBase * const meshBase) :
		m_meshBase(meshBase),
		m_data(nullptr)
	{
		MeshRendererData * data = LOADED_MESH_RENDERERS[m_meshBase->getFilePath()];

		// This is a new mesh renderer
		if (data == nullptr)
		{
			m_data = new MeshRendererData;
			m_data->addReference();

			// Process vertices and upload them to GPU
			processVerticesAndUploadToGPU();

			LOADED_MESH_RENDERERS[m_meshBase->getFilePath()] = m_data;
		}
		// This is an existing mesh renderer
		else
		{
			m_data = data;
			m_data->addReference();
		}

		MLOG_DEBUG("MeshRenderer::MeshRenderer, created. FilePath: %s, ref amount: %d", m_meshBase->getFilePath().c_str(), m_data->getRefAmount());
	}

	MeshRenderer::~MeshRenderer()
	{
		m_data->delReference();

		if (m_data->getRefAmount() <= 0)
		{
			LOADED_MESH_RENDERERS.erase(m_meshBase->getFilePath());
			MDELETES(m_data);

			MLOG_DEBUG("MeshRenderer::~MeshRenderer, destroyed. FilePath: %s", m_meshBase->getFilePath().c_str());
		}
	}

	void MeshRenderer::render()
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);

		glBindVertexArray(m_data->getVao());
		glBindBuffer(GL_ARRAY_BUFFER, m_data->getVbo());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, BUFFER_OFFSET(0));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, BUFFER_OFFSET(12));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, BUFFER_OFFSET(24));
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, Vertex::SIZE * 4, BUFFER_OFFSET(36));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->getIbo());
		glDrawElements(GL_TRIANGLES, m_meshBase->getData()->getSize(), GL_UNSIGNED_INT, NULL);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
	}

	MeshBase * const MeshRenderer::getMeshBase()
	{
		return m_meshBase;
	}

	MeshRendererData * const MeshRenderer::getData()
	{
		return m_data;
	}

	Transform * const MeshRenderer::getTransform()
	{
		return m_meshBase->getTransform();
	}

	void MeshRenderer::processVerticesAndUploadToGPU()
	{
		// Get the indice data into temp vector
		std::vector<uint32_t> indices(m_meshBase->getData()->getSize());

		for (size_t i = 0; i < indices.size(); i++)
		{
			indices[i] = i;
		}

		// Get the vertex data into temp reference vector
		std::vector<Vertex> & vertices(m_meshBase->getData()->getVertices());

		// Upload vertices to GPU
		glBindBuffer(GL_ARRAY_BUFFER, m_data->getVbo());
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * Vertex::SIZE * sizeof(float), &vertices[0], GL_STATIC_DRAW);

		// Upload indices to GPU
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->getIbo());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	}

}