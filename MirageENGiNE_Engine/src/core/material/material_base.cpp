#include "material_base.h"

// mirage includes
#include "graphics/material/texture.h"

namespace mirage
{

	MaterialBase::MaterialBase(
		Texture * const texAlbedo,
		glm::vec3 colAlbedo
	) :
		m_texAlbedo(texAlbedo),
		m_colAlbedo(colAlbedo)
	{

	}

	void MaterialBase::setTexAlbedo(Texture * const texAlbedo)
	{
		m_texAlbedo = texAlbedo;
	}

	Texture * const MaterialBase::getTexAlbedo() const
	{
		return m_texAlbedo;
	}

	void MaterialBase::setColAlbedo(const glm::vec3 & colAlbedo)
	{
		m_colAlbedo = colAlbedo;
	}

	glm::vec3 MaterialBase::getColAlbedo() const
	{
		return m_colAlbedo;
	}

}