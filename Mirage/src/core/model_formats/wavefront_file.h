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

	struct RGBA
	{
		float r, g, b, a;

		RGBA(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f) :
			r(r),
			g(g),
			b(b),
			a(a)
		{

		}
	};

	class WavefrontFace
	{
	public:
		std::vector<int> points;
		std::vector<int> normals;
		std::vector<int> texcoords;
		std::string material;

		WavefrontFace(const std::string & material = "NULL") :
			points(3),
			normals(3),
			texcoords(3),
			material(material)
		{

		}
	};

	class WavefrontMaterial
	{
	public:
		uint16_t illum;		// Illumination mode
		std::string KdText;	// Diffuse texture
		std::string KsText;	// Specular texture
		std::string KeText;	// Emissive texture
		RGBA Ka;			// Ambient color
		RGBA Kd;			// Diffuse color
		RGBA Ks;			// Specular color
		RGBA Ke;			// Emissive color
		double Ns;			// Specular exponent
		double Ni;			// Index of refraction
		double Fr;			// Fresnel reflectance

		WavefrontMaterial(
			const uint16_t illum = 0,
			const std::string & KdText = "",
			const std::string & KsText = "",
			const std::string & KeText = "",
			const RGBA & Ka = RGBA(),
			const RGBA & Kd = RGBA(),
			const RGBA & Ks = RGBA(),
			const RGBA & Ke = RGBA(),
			const double Ns = 100.0f,
			const double Ni = 1.0f,
			const double Fr = 0.75f
		) :
			illum(illum),
			KdText(KdText),
			KsText(KsText),
			KeText(KeText),
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
		bool hasNormals;
		bool hasTexcoords;

		WavefrontMesh() :
			faces(0),
			hasNormals(false),
			hasTexcoords(false)
		{

		}
	};

	class WavefrontFile
	{
	public:
		WavefrontFile(const std::string & filePath = "NULL");
		~WavefrontFile();
		void loadObj(const std::string & filePath);
		void loadMtl(const std::string & filePath);
		std::string getObjFilePath() const;
		std::string getMtlFilePath() const;
		const std::vector<glm::vec3> & getPoints() const;
		const std::vector<glm::vec3> & getNormals() const;
		const std::vector<glm::vec2> getTexcoords() const;
		const std::map<std::string, WavefrontMesh> & getMeshes() const;
		const std::map<std::string, WavefrontMaterial> & getMaterials() const;
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