#ifndef WAVEFRONT_FILE_H
#define WAVEFRONT_FILE_H

// std includes
#include <string>
#include <vector>
#include <map>

// lib includes
#include <glm/glm.hpp>

namespace mirage
{

	struct WavefrontColor
	{
		float r, g, b, a;

		WavefrontColor(
			float r = 0.0f,
			float g = 0.0f,
			float b = 0.0f,
			float a = 0.0f
		) :
			r(r),
			g(g),
			b(b),
			a(a)
		{

		}
	};

	struct WavefrontFace
	{
		std::vector<int> points;
		std::vector<int> normals;
		std::vector<int> texcoords;

		WavefrontFace() :
			points(3),
			normals(3),
			texcoords(3)
		{

		}
	};

	struct WavefrontMaterial
	{
		uint8_t illum;		// Illumination mode
		std::string KdTex;	// Diffuse texture
		std::string KsTex;	// Specular texture
		std::string KeTex;	// Emissive texture
		WavefrontColor Ka;  // Ambient color
		WavefrontColor Kd;  // Diffuse color
		WavefrontColor Ks;  // Specular color
		WavefrontColor Ke;  // Emissive color
		float Ns;			// Specular exponent
		float Ni;			// Index of refraction
		float Fr;			// Fresnel reflectance

		WavefrontMaterial(
			uint8_t illum = 0,
			std::string KdTex = "",
			std::string KsTex = "",
			std::string KeTex = "",
			WavefrontColor Ka = WavefrontColor(),
			WavefrontColor Kd = WavefrontColor(),
			WavefrontColor Ks = WavefrontColor(),
			WavefrontColor Ke = WavefrontColor(),
			float Ns = 100.0,
			float Ni = 1.0,
			float Fr = 0.75
		) :
			illum(illum),
			KdTex(KdTex),
			KsTex(KsTex),
			KeTex(KeTex),
			Ka(Ka),
			Kd(Kd),
			Ks(Ks),
			Ke(Ke),
			Ns(Ns),
			Ni(Ni),
			Fr(Fr)
		{

		}
	};

	class WavefrontMesh
	{
	public:
		std::vector<WavefrontFace> faces;
		std::string mesh_identifier;
		std::string material_identifier;
		bool hasNormals;
		bool hasTexcoords;

		WavefrontMesh() :
			faces(0),
			mesh_identifier("NULL"),
			material_identifier("NULL"),
			hasNormals(false),
			hasTexcoords(false)
		{

		}
	};

	class WavefrontFile
	{
	public:
		WavefrontFile(const std::string & filePath);
		~WavefrontFile();

		void loadObj(const std::string & filePath);
		void loadMtl(const std::string & filePath);
		std::string getObjFilePath() const;
		std::string getMtlFilePath() const;
		std::vector<glm::vec3> & getPoints();
		std::vector<glm::vec3> & getNormals();
		std::vector<glm::vec2> getTexcoords();
		std::map<std::string, WavefrontMesh> & getMeshes();
		std::map<std::string, WavefrontMaterial> & getMaterials();
	private:
		std::string m_objFilePath;
		std::string m_mtlFilePath;
		std::vector<glm::vec3> m_points;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec2> m_texcoords;
		std::map<std::string, WavefrontMesh> m_meshes;
		std::map<std::string, WavefrontMaterial> m_materials;
	};

}

#endif // WAVEFRONT_FILE_H