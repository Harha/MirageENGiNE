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
		FLD_Y,
		FLD_Z
	};

	class FreeLook : public GameComponent
	{
	public:
		FreeLook(
			float sensitivity = 0.1f,
			float rollSpeed = 0.25f,
			const std::string & identifier = "freelook"
		);
		~FreeLook();

		virtual void update(float dt) override;
		virtual void render(GraphicsEngine * const gfxEngine) override;
		void look(FreeLookDirection_t direction, float delta, float dt);
		void setSensitivity(float sensitivity);
		float getSensitivity() const;
		void setRollSpeed(float rollSpeed);
		float getRollSpeed() const;
	private:
		float m_sensitivity;
		float m_rollSpeed;
	};

}

#endif // FREELOOK_H