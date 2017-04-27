#ifndef FREEMOVE_H
#define FREEMOVE_H

#include "game/gcomponent.h"

// std includes
#include <string>
#include <vector>

namespace mirage
{

	class GraphicsEngine;
	class GameObject;

	enum FreeMoveDirection_t : uint8_t
	{
		FMD_FORWARD = 0,
		FMD_BACKWARD = 1,
		FMD_LEFT = 2,
		FMD_RIGHT = 3,
		FMD_UP = 4,
		FMD_DOWN = 5
	};

	class FreeMove : public GameComponent
	{
	public:
		FreeMove(
			float speed = 1.0f,
			const std::string & identifier = "freemove"
		);
		~FreeMove();

		virtual void update(float dt) override;
		virtual void render(GraphicsEngine * const gfxEngine) override;
		void move(FreeMoveDirection_t direction, float dt);
		float setSpeed(float speed);
		float getSpeed() const;
	private:
		float m_speed;
	};

}

#endif // FREEMOVE_H