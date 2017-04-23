#include "material_base.h"

namespace mirage
{

	MaterialBase::MaterialBase(
		glm::vec3 colorDiffuse,
		glm::vec3 colorSpecular
	) :
		m_colorDiffuse(colorDiffuse),
		m_colorSpecular(colorSpecular)
	{

	}

	void MaterialBase::setColorDiffuse(const glm::vec3 & colorDiffuse)
	{
		m_colorDiffuse = colorDiffuse;
	}

	glm::vec3 MaterialBase::getColorDiffuse() const
	{
		return m_colorDiffuse;
	}

	void MaterialBase::setColorSpecular(const glm::vec3 & colorSpecular)
	{
		m_colorSpecular = colorSpecular;
	}

	glm::vec3 MaterialBase::getColorSpecular() const
	{
		return m_colorSpecular;
	}

}