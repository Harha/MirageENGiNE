#include "material_base.h"

// mirage includes
#include "graphics/material/texture.h"

namespace mirage
{

	MaterialBase::MaterialBase(
		Texture * const textureDiffuse,
		glm::vec3 colorDiffuse,
		glm::vec3 colorSpecular
	) :
		m_textureDiffuse(textureDiffuse),
		m_colorDiffuse(colorDiffuse),
		m_colorSpecular(colorSpecular)
	{

	}

	void MaterialBase::setTextureDiffuse(Texture * const textureDiffuse)
	{
		m_textureDiffuse = textureDiffuse;
	}

	Texture * const MaterialBase::getTextureDiffuse() const
	{
		return m_textureDiffuse;
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