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
			glm::vec3 color_kd = glm::vec3(1, 1, 1),
			glm::vec3 color_ks = glm::vec3(1, 1, 1)
		);

		void setColorKd(const glm::vec3 & color_kd);
		void setColorKs(const glm::vec3 & color_ks);
		glm::vec3 getColorKd() const;
		glm::vec3 getColorKs() const;
	private:
		glm::vec3 m_color_kd;
		glm::vec3 m_color_ks;
	};

}

#endif // MATERIAL_BASE_H