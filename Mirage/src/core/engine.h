#ifndef ENGINE_H
#define ENGINE_H

// std includes
#include <string>

// mirage includes
#include "../config.h"
#include "../macros.h"
#include "../util/inifile.h"

// forward declarations
class Window;
class GraphicsEngine;

namespace mirage
{

	class CoreEngine
	{
	public:
		CoreEngine(const std::string & config = "./res/config.ini");
		~CoreEngine();
		const IniFile & getConfig() const;
		Window * const getWindow() const;
		GraphicsEngine * const getGraphicsEngine() const;
	private:
		IniFile m_config;
		Window * m_window;
		GraphicsEngine * m_graphicsEngine;
	};

}

#endif // ENGINE_H