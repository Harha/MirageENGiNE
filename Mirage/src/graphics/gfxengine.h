#ifndef GFXENGINE_H
#define GFXENGINE_H

// std includes
#include <string>
#include <vector>
#include <map>

namespace mirage
{

	enum EngineRunState;
	class CoreEngine;
	class Camera;
	class RenderCMD;
	class ShaderProgram;

	class GraphicsEngine
	{
	public:
		GraphicsEngine(CoreEngine * const coreEngine = nullptr);
		~GraphicsEngine();
		void initialize();
		void render();
		void glErrorCheck();
		void setCurrentCamera(Camera * const camera);
		Camera * const getCurrentCamera() const;
		void pushRenderCMD(RenderCMD * const r_cmd);
		ShaderProgram * const getShaderProgram(const std::string & name);
	private:
		EngineRunState m_runState;
		CoreEngine * m_coreEngine;
		Camera * m_currentCamera;
		std::vector<RenderCMD *> m_renderCmds;
		std::map <std::string, ShaderProgram *> m_shaderPrograms;
	};

}

#endif // GFXENGINE_H