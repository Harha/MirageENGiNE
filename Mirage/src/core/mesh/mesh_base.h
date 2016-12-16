#ifndef MESH_H
#define MESH_H

// std includes
#include <string>
#include <vector>
#include <map>

// mirage includes
#include "core/vertex.h"
#include "core/transform.h"

typedef int GLsizei;

namespace mirage
{

	class MeshBaseData
	{
	public:
		MeshBaseData(
			std::vector<Vertex> vertices = std::vector<Vertex>()
		);
		~MeshBaseData();
		void setSize(GLsizei size);
		void addReference();
		void delReference();
		std::vector<Vertex> & getVertices();
		const GLsizei getSize() const;
		const int32_t getRefAmount() const;
	private:
		std::vector<Vertex> m_vertices;
		GLsizei m_size;
		int32_t m_refAmount;
	};

	extern std::map<std::string, MeshBaseData *> LOADED_BASE_MESHES;

	class MeshBase
	{
	public:
		MeshBase(
			const std::string & filePath = "null",
			Transform transform = Transform(),
			std::vector<Vertex> vertices = std::vector<Vertex>()
		);
		~MeshBase();
		const std::string getFilePath() const;
		MeshBaseData * const getData();
		Transform & getTransform();
	private:
		std::string m_filePath;
		MeshBaseData * m_data;
		Transform m_transform;
	};

}

#endif // MESH_H