#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

// std includes
#include <map>

typedef unsigned int GLuint;

namespace mirage
{

	class MeshBase;
	class Transform;

	class MeshRendererData
	{
	public:
		MeshRendererData();
		~MeshRendererData();

		const GLuint getVao() const;
		const GLuint getVbo() const;
		const GLuint getIbo() const;
		void addReference();
		void delReference();
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
		MeshBase * const getMeshBase();
		MeshRendererData * const getData();
		Transform * const getTransform();
	private:
		void processVerticesAndUploadToGPU();

		MeshBase * m_meshBase;
		MeshRendererData * m_data;
	};

}

#endif // MESH_RENDERER_H