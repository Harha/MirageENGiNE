#ifndef MATERIAL_BASE_H
#define MATERIAL_BASE_H

// lib includes
#include <glm/glm.hpp>

namespace mirage
{

	class MaterialBase
	{
	public:
		MaterialBase(
			glm::vec3 colorDiffuse = glm::vec3(1, 1, 1),
			glm::vec3 colorSpecular = glm::vec3(1, 1, 1)
		);

		void setColorDiffuse(const glm::vec3 & colorDiffuse);
		glm::vec3 getColorDiffuse() const;
		void setColorSpecular(const glm::vec3 & colorSpecular);
		glm::vec3 getColorSpecular() const;
	private:
		glm::vec3 m_colorDiffuse;
		glm::vec3 m_colorSpecular;
	};

}

#endif // MATERIAL_BASE_H