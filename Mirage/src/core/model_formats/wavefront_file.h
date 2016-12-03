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
		RGBA Ka; // Ambient color
		RGBA Kd; // Diffuse color
		RGBA Ks; // Specular color
		RGBA Ke; // Emissive color

		WavefrontMaterial(const RGBA & Ka = RGBA(), const RGBA & Kd = RGBA(), const RGBA & Ks = RGBA(), const RGBA & Ke = RGBA()) :
			Ka(Ka),
			Kd(Kd),
			Ks(Ks),
			Ke(Ke)
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
		void loadObj(const std::string & filePath);
		void loadMtl(const std::string & filePath);
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