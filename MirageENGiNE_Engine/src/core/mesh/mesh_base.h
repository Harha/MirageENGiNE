#ifndef MESH_BASE_H
#define MESH_BASE_H

// std includes
#include <string>
#include <vector>
#include <map>

// mirage includes
#include "core/vertex.h"
#include "core/transform.h"
#include "core/material/material_base.h"

typedef int GLsizei;

namespace mirage
{

	class MeshBaseData
	{
	public:
		MeshBaseData(
			const std::vector<Vertex> & vertices = std::vector<Vertex>(),
			MaterialBase material = MaterialBase()
		);
		~MeshBaseData();

		void setVertices(const std::vector<Vertex> & vertices);
		std::vector<Vertex> & getVertices();
		void setMaterial(MaterialBase material);
		MaterialBase & getMaterial();
		void setSize(GLsizei size);
		const GLsizei getSize() const;
		void addReference();
		void delReference();
		const int32_t getRefAmount() const;
	private:
		std::vector<Vertex> m_vertices;
		MaterialBase m_material;
		GLsizei m_size;
		int32_t m_refAmount;
	};

	extern std::map<std::string, MeshBaseData *> LOADED_BASE_MESHES;

	class MeshBase
	{
	public:
		MeshBase(
			const std::string & filePath,
			const std::vector<Vertex> & vertices = std::vector<Vertex>(),
			MaterialBase material = MaterialBase()
		);
		~MeshBase();

		const std::string getFilePath() const;
		MeshBaseData * const getData();
		void setTransform(Transform * const transform);
		Transform * const getTransform() const;
	private:
		std::string m_filePath;
		MeshBaseData * m_data;
		Transform * m_transform;
	};

}

#endif // MESH_BASE_H