#ifndef GCOMPONENT_H
#define GCOMPONENT_H

// std includes
#include <string>

namespace mirage
{

	class GraphicsEngine;
	class GameObject;

	enum GameComponent_t : uint8_t
	{
		GC_GENERIC = 0,
		GC_CAMERA_PERSPECTIVE = 1,
		GC_CAMERA_ORTHOGRAPHIC = 2,
		GC_MODEL_BASIC = 3
	};

	class GameComponent
	{
	public:
		GameComponent(
			GameComponent_t type = GC_GENERIC,
			const std::string & identifier = "GameComponent"
		);
		virtual ~GameComponent();

		virtual void update(float dt) = 0;
		virtual void render(GraphicsEngine * const gfxEngine) = 0;
		virtual GameComponent_t getType() const;
		virtual void setIdentifier(const std::string & identifier);
		virtual const std::string & getIdentifier() const;
		virtual void setParent(GameObject * const parent);
		virtual GameObject * const getParent() const;
	private:
	protected:
		GameComponent_t m_type;
		std::string m_identifier;
		GameObject * m_parent;
	};

}

#endif // GCOMPONENT_H