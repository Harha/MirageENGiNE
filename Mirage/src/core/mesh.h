#ifndef MESH_H
#define MESH_H

// std includes
#include <iostream>
#include <string>
#include <map>

// mirage includes
#include "../config.h"
#include "../macros.h"

// forward declarations
typedef unsigned int GLuint;

namespace mirage
{

	class MeshData
	{
	public:
		MeshData();
		~MeshData();
		void addReference();
		void delReference();
		const GLuint getVao() const;
		const GLuint getVbo() const;
		const GLuint getIbo() const;
		const int32_t getRefAmount() const;
	private:
		GLuint m_vao;
		GLuint m_vbo;
		GLuint m_ibo;
		int32_t m_refAmount;
	};

	extern std::map<std::string, MeshData *> LOADED_MESHES;

	class Mesh
	{

	public:
		Mesh(const std::string & filePath = "null");
		~Mesh();
		void render();
		const std::string getFilePath() const;
		MeshData * const getData();
	private:
		std::string m_filePath;
		MeshData * m_data;
	};

}

#endif // MESH_H