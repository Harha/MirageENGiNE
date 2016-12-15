#include "mesh_base.h"

// lib includes
#include "glad/glad.h"

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

	MeshBaseData::MeshBaseData(std::vector<Vertex> vertices) :
		m_vertices(vertices),
		m_size(vertices.size()),
		m_refAmount(0)
	{
		MLOG_INFO("MeshData::MeshBaseData initialized. Size: %d", m_size);
	}

	MeshBaseData::~MeshBaseData()
	{
	}

	void MeshBaseData::setSize(GLsizei size)
	{
		m_size = size;
	}

	void MeshBaseData::addReference()
	{
		m_refAmount++;
	}

	void MeshBaseData::delReference()
	{
		m_refAmount = (m_refAmount - 1 < 0) ? 0 : m_refAmount - 1;
	}

	std::vector<Vertex> & MeshBaseData::getVertices()
	{
		return m_vertices;
	}

	const GLsizei MeshBaseData::getSize() const
	{
		return m_size;
	}

	const int32_t MeshBaseData::getRefAmount() const
	{
		return m_refAmount;
	}

	// ---------------------------------------------------------------------------
	// MeshBase
	// ---------------------------------------------------------------------------

	std::map<std::string, MeshBaseData *> LOADED_BASE_MESHES;

	MeshBase::MeshBase(const std::string & filePath, Transform transform) :
		m_filePath(filePath),
		m_data(nullptr),
		m_transform(transform)
	{
		MeshBaseData * data = LOADED_BASE_MESHES[m_filePath];

		// This is a new mesh base
		if (data == nullptr)
		{
			// Vector of mesh vertices
			std::vector<Vertex> vertices;

			// Import wavefront mesh
			if (filetoextension(m_filePath) == "obj")
			{
				// Load it into memory
				WavefrontFile file = WavefrontFile(m_filePath);

				// Get the file data into temp references
				auto & points = file.getPoints();
				auto & normals = file.getNormals();
				auto & texcoords = file.getTexcoords();
				auto & meshes = file.getMeshes();
				auto & materials = file.getMaterials();

				// Export vertices from each mesh
				for (auto const & mesh : meshes)
				{
					for (auto const & face : mesh.second.faces)
					{
						for (size_t i = 0; i < 3; i++)
						{
							glm::vec3 point;
							glm::vec3 normal;
							glm::vec3 tangent;
							glm::vec2 uv;

							if (face.points.size() == 3)
								point = points[face.points[i]];

							if (face.normals.size() == 3)
								normal = normals[face.normals[i]];

							if (face.texcoords.size() == 3)
								uv = texcoords[face.texcoords[i]];

							vertices.push_back(Vertex(point, normal, tangent, uv));
						}
					}
				}
			}

			m_data = new MeshBaseData(vertices);
			m_data->addReference();
			LOADED_BASE_MESHES[m_filePath] = m_data;
		}
		// This is an existing mesh base
		else
		{
			m_data = data;
			m_data->addReference();
		}

		MLOG_INFO("MeshBase::MeshBase initialized. FilePath: %s, reference amount: %d", m_filePath.c_str(), m_data->getRefAmount());
	}

	MeshBase::~MeshBase()
	{
		m_data->delReference();

		if (m_data->getRefAmount() <= 0)
		{
			LOADED_BASE_MESHES.erase(m_filePath);
			MDELETES(m_data);

			MLOG_INFO("MeshBase::~MeshBase destroyed. FilePath: %s", m_filePath.c_str());
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

	Transform & MeshBase::getTransform()
	{
		return m_transform;
	}


}