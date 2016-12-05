#include "mesh.h"

// lib includes
#include "glad/glad.h"

// mirage includes
#include "config.h"
#include "macros.h"

namespace mirage
{

	// ---------------------------------------------------------------------------
	// MeshData
	// ---------------------------------------------------------------------------

	MeshData::MeshData(GLsizei size) :
		m_vao(0),
		m_vbo(0),
		m_ibo(0),
		m_size(size),
		m_refAmount(0)
	{
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);

		MLOG_INFO("MeshData::MeshData initialized successfully, VAO: %d, VBO: %d, IBO: %d", m_vao, m_vbo, m_ibo);
	}

	MeshData::~MeshData()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ibo);
	}

	void MeshData::setSize(GLsizei size)
	{
		m_size = size;
	}

	void MeshData::addReference()
	{
		m_refAmount++;
	}

	void MeshData::delReference()
	{
		m_refAmount = (m_refAmount - 1 < 0) ? 0 : m_refAmount - 1;
	}

	const GLuint MeshData::getVao() const
	{
		return m_vao;
	}

	const GLuint MeshData::getVbo() const
	{
		return m_vbo;
	}

	const GLuint MeshData::getIbo() const
	{
		return m_ibo;
	}

	const GLsizei MeshData::getSize() const
	{
		return m_size;
	}

	const int32_t MeshData::getRefAmount() const
	{
		return m_refAmount;
	}

	// ---------------------------------------------------------------------------
	// Mesh
	// ---------------------------------------------------------------------------

	std::map<std::string, MeshData *> LOADED_MESHES;

	Mesh::Mesh(const std::string & filePath, Transform transform) :
		m_filePath(filePath),
		m_data(nullptr),
		m_transform(transform)
	{
		MeshData * data = LOADED_MESHES[m_filePath];

		// This is a new mesh
		if (data == nullptr)
		{
			m_data = new MeshData;
			m_data->addReference();
			LOADED_MESHES[m_filePath] = m_data;
		}
		// This is an existing mesh
		else
		{
			m_data = data;
			m_data->addReference();
		}

		MLOG_INFO("Mesh::Mesh initialized successfully. FilePath: %s, reference amount: %d", m_filePath.c_str(), m_data->getRefAmount());
	}

	Mesh::~Mesh()
	{
		m_data->delReference();

		if (m_data->getRefAmount() <= 0)
		{
			LOADED_MESHES.erase(m_filePath);
			MDELETES(m_data);

			MLOG_INFO("Mesh::~Mesh, destroying mesh. FilePath: %s", m_filePath.c_str());
		}
	}

	const std::string Mesh::getFilePath() const
	{
		return m_filePath;
	}

	MeshData * const Mesh::getData()
	{
		return m_data;
	}

	Transform & Mesh::getTransform()
	{
		return m_transform;
	}


}