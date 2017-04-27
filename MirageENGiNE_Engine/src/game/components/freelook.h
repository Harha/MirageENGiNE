#ifndef FREELOOK_H
#define FREELOOK_H

#include "game/gcomponent.h"

// std includes
#include <string>
#include <vector>

namespace mirage
{

	class GraphicsEngine;
	class GameObject;

	enum FreeLookDirection_t : uint8_t
	{
		FLD_X,
		FLD_Y
	};

	class FreeLook : public GameComponent
	{
	public:
		FreeLook(
			float sensitivity = 1.0f,
			const std::string & identifier = "freelook"
		);
		~FreeLook();

		virtual void update(float dt) override;
		virtual void render(GraphicsEngine * const gfxEngine) override;
		void rotate(FreeLookDirection_t direction, float delta, float dt);
		float setSensitivity(float sensitivity);
		float getSensitivity() const;
	private:
		float m_sensitivity;
	};

}

#endif // FREELOOK_H