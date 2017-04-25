#ifndef RENDERCMD_H
#define RENDERCMD_H

// std includes
#include <vector>

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
			std::vector<MeshRenderer *> meshRenderers
		);

		ShaderProgram * const getProgram() const;
		Camera * const getCamera() const;
		const std::vector<MeshRenderer *> & getMeshRenderers() const;
	private:
		ShaderProgram * m_program;
		Camera * m_camera;
		std::vector<MeshRenderer *> m_meshRenderers;
	};
}


#endif // RENDERCMD_H