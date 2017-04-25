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
		std::vector<MeshRenderer *> meshRenderers
	) :
		m_program(program),
		m_camera(camera),
		m_meshRenderers(meshRenderers)
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

	const std::vector<MeshRenderer *> & RenderCMD::getMeshRenderers() const
	{
		return m_meshRenderers;
	}

}