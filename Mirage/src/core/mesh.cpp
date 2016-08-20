#include "mesh.h"

// lib includes
#include "../glad/glad.h"

namespace mirage
{

	// ---------------------------------------------------------------------------
	// MeshData
	// ---------------------------------------------------------------------------

	MeshData::MeshData() :
		m_vao(0),
		m_vbo(0),
		m_ibo(0),
		m_refAmount(0)
	{
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);

		MLOG("MeshData::MeshData - VAO: " << m_vao << ", VBO: " << m_vbo << ", IBO: " << m_ibo);
	}

	MeshData::~MeshData()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ibo);
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

	const int32_t MeshData::getRefAmount() const
	{
		return m_refAmount;
	}

	// ---------------------------------------------------------------------------
	// Mesh
	// ---------------------------------------------------------------------------

	std::map<std::string, MeshData *> LOADED_MESHES;

	Mesh::Mesh(const std::string & filePath) :
		m_filePath(filePath),
		m_data(nullptr)
	{
		MeshData * data = LOADED_MESHES[m_filePath];

		// This is a new mesh
		if (data == nullptr)
		{
			m_data = new MeshData;
			m_data->addReference();
			LOADED_MESHES[m_filePath] = m_data;

			MLOG("Mesh::Mesh - Loaded a new mesh object into memory. FilePath: " << m_filePath);
		}
		// This is an existing mesh
		else
		{
			m_data = data;
			m_data->addReference();

			MLOG("Mesh::Mesh - Loaded an existing mesh object into memory."
				<< "FilePath: " << m_filePath << ", RefAmount: " << m_data->getRefAmount());
		}
	}

	Mesh::~Mesh()
	{
		m_data->delReference();

		if (m_data->getRefAmount() <= 0)
		{
			MLOG("Mesh::~Mesh - Destroying mesh. FilePath: " << m_filePath);

			LOADED_MESHES.erase(m_filePath);
			MDELETES(m_data);
		}
	}

	void Mesh::render()
	{

	}

	const std::string Mesh::getFilePath() const
	{
		return m_filePath;
	}

	MeshData * const Mesh::getData()
	{
		return m_data;
	}


}