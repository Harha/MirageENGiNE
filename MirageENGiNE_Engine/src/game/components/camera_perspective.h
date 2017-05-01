#ifndef CAMERA_PERSPECTIVE_H
#define CAMERA_PERSPECTIVE_H

#include "game/gcomponent.h"

// std includes
#include <string>

namespace mirage
{

	class GraphicsEngine;
	class GameObject;
	class Camera;

	struct CameraPerspectiveSettings
	{
		float fov;
		float aspect;
		float nearplane;
		float farplane;
	};

	class CameraPerspective : public GameComponent
	{
	public:
		CameraPerspective(
			float fov = 70.0f,
			float aspect = 1.0f,
			float nearplane = 0.1f,
			float farplane = 1028.0f,
			float exposure = 1.0f,
			const std::string & identifier = "camera_perspective"
		);
		~CameraPerspective();

		virtual void update(float dt) override;
		virtual void render(GraphicsEngine * const gfxEngine) override;
		virtual void setParent(GameObject * const parent) override;
		void setSettings(const CameraPerspectiveSettings & settings);
		const CameraPerspectiveSettings & getSettings() const;
		Camera * const getCamera() const;
	private:
		CameraPerspectiveSettings m_settings;
		Camera * m_camera;
	};

}

#endif // CAMERA_PERSPECTIVE_H