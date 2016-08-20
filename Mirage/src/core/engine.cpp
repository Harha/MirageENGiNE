#include "engine.h"

// mirage includes
#include "../graphics/window.h"
#include "../graphics/gfxengine.h"

namespace mirage
{

	CoreEngine::CoreEngine(const std::string & configPath) :
		m_config(configPath),
		m_window(nullptr),
		m_graphicsEngine(nullptr)
	{
		// Initialize window
		m_window = new Window(
			m_config.getString("[gfx]", "windowT"),
			m_config.getInt("[gfx]", "windowW"),
			m_config.getInt("[gfx]", "windowH"),
			m_config.getBool("[gfx]", "fullscreen")
		);

		// Initialize graphics engine

		MLOG("CoreEngine: Initialized successfully. Config file: " << m_config.getPath());
	}

	CoreEngine::~CoreEngine()
	{
		MDELETES(m_window);
		MDELETES(m_graphicsEngine);
	}

	const IniFile & CoreEngine::getConfig() const
	{
		return m_config;
	}

	Window * const CoreEngine::getWindow() const
	{
		return m_window;
	}

	GraphicsEngine * const CoreEngine::getGraphicsEngine() const
	{
		return m_graphicsEngine;
	}

}