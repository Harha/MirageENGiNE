#ifndef RENDERCMD_H
#define RENDERCMD_H

// std includes
#include <vector>

// lib includes
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace mirage
{

	class ShaderProgram;
	class Camera;
	class MeshRenderer;

	class RenderCMD
	{
	public:
		RenderCMD(
			ShaderProgram * const program,
			Camera * const camera,
			std::vector<MeshRenderer *> meshes
		);

		ShaderProgram * const getProgram() const;
		Camera * const getCamera() const;
		std::vector<MeshRenderer *> getMeshes() const;
	private:
		ShaderProgram * m_program;
		Camera * m_camera;
		std::vector<MeshRenderer *> m_meshes;
	};
}


#endif // RENDERCMD_H