#ifndef GFXENGINE_H
#define GFXENGINE_H

// std includes
#include <string>

namespace mirage
{

	enum EngineRunState;
	class CoreEngine;

	class GraphicsEngine
	{
	public:
		GraphicsEngine(CoreEngine * const coreEngine = nullptr);
		~GraphicsEngine();
		void render();
		void glErrorCheck();
	private:
		EngineRunState m_runState;
		CoreEngine * m_coreEngine;
	};

}

#endif // GFXENGINE_H