#ifndef GFXENGINE_H
#define GFXENGINE_H

// std includes
#include <string>

// mirage includes
#include "../config.h"
#include "../macros.h"

namespace mirage
{

	// forward declarations
	enum EngineRunState;
	class CoreEngine;

	class GraphicsEngine
	{
	public:
		GraphicsEngine(CoreEngine * const coreEngine = nullptr);
		~GraphicsEngine();
		void render();
	private:
		EngineRunState m_runState;
		CoreEngine * m_coreEngine;
	};

}

#endif // GFXENGINE_H