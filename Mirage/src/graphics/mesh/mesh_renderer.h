#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

// std includes
#include <map>

// mirage includes
#include "core/vertex.h"
#include "core/transform.h"

typedef unsigned int GLuint;

namespace mirage
{

	class MeshBase;

	class MeshRendererData
	{
	public:
		MeshRendererData();
		~MeshRendererData();
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

	extern std::map<std::string, MeshRendererData *> LOADED_MESH_RENDERERS;

	class MeshRenderer
	{
	public:
		MeshRenderer(MeshBase * const meshBase = nullptr);
		~MeshRenderer();
		void render();
		void prepareVertices();
		MeshBase * const getMeshBase();
		MeshRendererData * const getData();
		Transform * const getTransform();
	private:
		MeshBase * m_meshBase;
		MeshRendererData * m_data;
	};

}

#endif // MESH_RENDERER_H