#include "mesh_base.h"

// lib includes
#include "3rdparty/glad/glad.h"

// mirage includes
#include "config.h"
#include "macros.h"
#include "util/strutil.h"
#include "core/model_formats/wavefront_file.h"

namespace mirage
{

	// ---------------------------------------------------------------------------
	// MeshBaseData
	// ---------------------------------------------------------------------------

	MeshBaseData::MeshBaseData(
		std::vector<Vertex> vertices,
		MaterialBase material
	) :
		m_vertices(vertices),
		m_material(material),
		m_size(vertices.size()),
		m_refAmount(0)
	{
		MLOG_DEBUG("MeshData::MeshBaseData, created. Size: %d", m_size);
	}

	MeshBaseData::~MeshBaseData()
	{

	}

	void MeshBaseData::setVertices(std::vector<Vertex> vertices)
	{
		m_vertices = vertices;
	}

	std::vector<Vertex> & MeshBaseData::getVertices()
	{
		return m_vertices;
	}

	void MeshBaseData::setMaterial(MaterialBase material)
	{
		m_material = material;
	}

	MaterialBase & MeshBaseData::getMaterial()
	{
		return m_material;
	}

	void MeshBaseData::setSize(GLsizei size)
	{
		m_size = size;
	}

	const GLsizei MeshBaseData::getSize() const
	{
		return m_size;
	}

	void MeshBaseData::addReference()
	{
		m_refAmount++;
	}

	void MeshBaseData::delReference()
	{
		m_refAmount = (m_refAmount - 1 < 0) ? 0 : m_refAmount - 1;
	}

	const int32_t MeshBaseData::getRefAmount() const
	{
		return m_refAmount;
	}

	// ---------------------------------------------------------------------------
	// MeshBase
	// ---------------------------------------------------------------------------

	std::map<std::string, MeshBaseData *> LOADED_BASE_MESHES;

	MeshBase::MeshBase(
		const std::string & filePath,
		std::vector<Vertex> vertices,
		MaterialBase material
	) :
		m_filePath(filePath),
		m_data(nullptr),
		m_transform(nullptr)
	{
		MeshBaseData * data = LOADED_BASE_MESHES[m_filePath];

		// This is a new mesh base
		if (data == nullptr)
		{
			m_data = new MeshBaseData(vertices, material);
			m_data->addReference();
			LOADED_BASE_MESHES[m_filePath] = m_data;
		}
		// This is an existing mesh base
		else
		{
			m_data = data;
			m_data->addReference();
		}

		MLOG_DEBUG("MeshBase::MeshBase, created. FilePath: %s, reference amount: %d", m_filePath.c_str(), m_data->getRefAmount());
	}

	MeshBase::~MeshBase()
	{
		m_data->delReference();

		// If no references to this left, deallocate memory
		if (m_data->getRefAmount() <= 0)
		{
			LOADED_BASE_MESHES.erase(m_filePath);
			MDELETES(m_data);

			MLOG_DEBUG("MeshBase::~MeshBase, destroyed. FilePath: %s", m_filePath.c_str());
		}
	}

	const std::string MeshBase::getFilePath() const
	{
		return m_filePath;
	}

	MeshBaseData * const MeshBase::getData()
	{
		return m_data;
	}

	void MeshBase::setTransform(Transform * const transform)
	{
		m_transform = transform;
	}

	Transform * const MeshBase::getTransform() const
	{
		return m_transform;
	}

}