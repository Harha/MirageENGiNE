#ifndef MATERIAL_BASE_H
#define MATERIAL_BASE_H

// lib includes
#include <glm/glm.hpp>

namespace mirage
{

	class Texture;

	class MaterialBase
	{
	public:
		MaterialBase(
			Texture * const texAlbedo = nullptr,
			glm::vec3 colAlbedo = glm::vec3(1, 1, 1)
		);

		void setTexAlbedo(Texture * const texAlbedo);
		Texture * const getTexAlbedo() const;
		void setColAlbedo(const glm::vec3 & colAlbedo);
		glm::vec3 getColAlbedo() const;
	private:
		Texture * m_texAlbedo;
		glm::vec3 m_colAlbedo;
	};

}

#endif // MATERIAL_BASE_H