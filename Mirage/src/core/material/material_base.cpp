#include "material_base.h"

namespace mirage
{

	MaterialBase::MaterialBase(
		glm::vec3 color_kd,
		glm::vec3 color_ks
	) :
		m_color_kd(color_kd),
		m_color_ks(color_ks)
	{

	}

	void MaterialBase::setColorKd(const glm::vec3 & color_kd)
	{
		m_color_kd = color_kd;
	}

	void MaterialBase::setColorKs(const glm::vec3 & color_ks)
	{
		m_color_ks = color_ks;
	}

	glm::vec3 MaterialBase::getColorKd() const
	{
		return m_color_kd;
	}

	glm::vec3 MaterialBase::getColorKs() const
	{
		return m_color_ks;
	}

}