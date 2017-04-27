#include "camera_perspective.h"

// lib includes
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// mirage includes
#include "macros.h"
#include "graphics/gfxengine.h"
#include "game/gobject.h"
#include "graphics/camera/camera.h"
#include "core/transform.h"

namespace mirage
{

	CameraPerspective::CameraPerspective(
		float fov,
		float aspect,
		float nearplane,
		float farplane,
		float exposure,
		const std::string & identifier
	) :
		GameComponent(GC_CAMERA_PERSPECTIVE, identifier),
		m_settings{ fov, aspect, nearplane, farplane },
		m_camera(new Camera(
			nullptr,
			glm::perspective(glm::radians(fov), aspect, nearplane, farplane),
			exposure
		))
	{
		MLOG_DEBUG(
			"CameraPerspective::CameraPerspective, created. Fov: %.2f, aspect: %.2f, near: %.2f, far: %.2f, exposure: %.2f",
			fov, aspect, nearplane, farplane, exposure
		);
	}

	CameraPerspective::~CameraPerspective()
	{
		MDELETES(m_camera);

		MLOG_DEBUG("CameraPerspective::~CameraPerspective, destroyed.");
	}

	void CameraPerspective::update(float dt)
	{

	}

	void CameraPerspective::render(GraphicsEngine * const gfxEngine)
	{

	}

	void CameraPerspective::setParent(GameObject * const parent)
	{
		m_parent = parent;
		m_camera->setTransform(&m_parent->getTransform());
	}

	void CameraPerspective::setSettings(const CameraPerspectiveSettings & settings)
	{
		m_settings = settings;
		m_camera->setProjectionMatrix(glm::perspective(glm::radians(settings.fov), settings.aspect, settings.nearplane, settings.farplane));
	}

	const CameraPerspectiveSettings & CameraPerspective::getSettings() const
	{
		return m_settings;
	}

	Camera * const CameraPerspective::getCamera() const
	{
		return m_camera;
	}

}