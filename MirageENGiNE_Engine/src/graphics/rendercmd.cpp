#include "graphics/rendercmd.h"

// mirage includes
#include "graphics/glsl/shader.h"
#include "graphics/camera/camera.h"
#include "graphics/mesh/mesh_renderer.h"

namespace mirage
{

	RenderCMD::RenderCMD(
		ShaderProgram * const program,
		Camera * const camera,
		std::vector<MeshRenderer *> meshes
	) :
		m_program(program),
		m_camera(camera),
		m_meshes(meshes)
	{

	}

	ShaderProgram * const RenderCMD::getProgram() const
	{
		return m_program;
	}

	Camera * const RenderCMD::getCamera() const
	{
		return m_camera;
	}

	std::vector<MeshRenderer *> RenderCMD::getMeshes() const
	{
		return m_meshes;
	}

}