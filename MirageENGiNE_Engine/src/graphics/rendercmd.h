#ifndef RENDERCMD_H
#define RENDERCMD_H

// std includes
#include <vector>

namespace mirage
{

	class ShaderProgram;
	class Camera;
	class MeshRenderer;

	enum RenderCMD_t : uint8_t
	{
		RCMD_DEBUG = 0,
		RCMD_GBUFFER = 1,
		RCMD_LIGHTING = 2,
		RCMD_POSTPROCESS = 3
	};

	class RenderCMD
	{
	public:
		RenderCMD(
			RenderCMD_t type,
			ShaderProgram * const program,
			Camera * const camera,
			std::vector<MeshRenderer *> meshRenderers
		);

		RenderCMD_t getType() const;
		ShaderProgram * const getProgram() const;
		Camera * const getCamera() const;
		const std::vector<MeshRenderer *> & getMeshRenderers() const;
	private:
		RenderCMD_t m_type;
		ShaderProgram * m_program;
		Camera * m_camera;
		std::vector<MeshRenderer *> m_meshRenderers;
	};
}


#endif // RENDERCMD_H