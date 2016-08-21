#ifndef RENDERABLE_MESH_H
#define RENDERABLE_MESH_H

namespace mirage
{

	// forward declarations
	class Mesh;

	class RenderableMesh
	{
	public:
		RenderableMesh(Mesh * mesh = nullptr);
		void render();
	private:
		Mesh * m_mesh;
	};

}

#endif // RENDERABLE_MESH_H