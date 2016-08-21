#ifndef MESH_H
#define MESH_H

// std includes
#include <iostream>
#include <string>
#include <map>

// mirage includes
#include "../config.h"
#include "../macros.h"
#include "transform.h"

// forward declarations
typedef unsigned int GLuint;
typedef int GLsizei;

namespace mirage
{

	// TODO: Maybe add bool that determines whether to generate VAO/VBO/IBO for the MeshData or not

	class MeshData
	{
	public:
		MeshData(GLsizei size = 0);
		~MeshData();
		void setSize(GLsizei size);
		void addReference();
		void delReference();
		const GLuint getVao() const;
		const GLuint getVbo() const;
		const GLuint getIbo() const;
		const GLsizei getSize() const;
		const int32_t getRefAmount() const;
	private:
		GLuint m_vao;
		GLuint m_vbo;
		GLuint m_ibo;
		GLsizei m_size;
		int32_t m_refAmount;
	};

	extern std::map<std::string, MeshData *> LOADED_MESHES;

	class Mesh
	{
	public:
		Mesh(const std::string & filePath = "null", Transform transform = Transform());
		~Mesh();
		const std::string getFilePath() const;
		MeshData * const getData();
		Transform & getTransform();
	private:
		std::string m_filePath;
		MeshData * m_data;
		Transform m_transform;
	};

}

#endif // MESH_H