#include "wavefront_file.h"

// std includes
#include <fstream>
#include <regex>
#include <sstream>

// mirage includes
#include "../../config.h"
#include "../../macros.h"
#include "../../util/strutil.h"

namespace mirage
{

	// ---------------------------------------------------------------------------
	// WavefrontFile
	// ---------------------------------------------------------------------------

	WavefrontFile::WavefrontFile(const std::string & filePath) :
		m_objFilePath(filePath),
		m_mtlFilePath("NULL"),
		m_points(),
		m_normals(),
		m_texcoords(),
		m_meshes(),
		m_materials()
	{
		try
		{
			loadObj(m_objFilePath);
		}
		catch (const std::exception & e)
		{
			MERR("WavefrontFile::WavefrontFile - Error loading WavefrontFile!"
				<< " .obj FilePath: " << m_objFilePath << ", .mtl FilePath: " << m_mtlFilePath);
		}
	}


	void WavefrontFile::loadObj(const std::string & filePath)
	{
		// Read the file into memory
		std::ifstream file(filePath);

		if (file.is_open() == false)
		{
			throw std::exception();
		}

		// State variables
		std::string currentMesh = "root";
		std::string currentMaterial = "root";
		glm::vec3 current_v3;
		glm::vec2 current_v2;
		m_meshes[currentMesh] = WavefrontMesh();
		m_materials[currentMaterial] = WavefrontMaterial();

		// Iterate through every line
		std::string l;
		while (std::getline(file, l))
		{
			// Trim any leading/trailing/extra ws
			l.erase(std::unique(l.begin(), l.end(), istwospace), l.end());

			// Line sstream
			std::istringstream l_stream(l);

			// Get the first split section in line
			std::string type;
			l_stream >> type;

			switch (cstr2int(type.c_str()))
			{
			case cstr2int("mtllib"):
				l_stream >> m_mtlFilePath;
				loadMtl(m_mtlFilePath);
				break;
			case cstr2int("v"):
				l_stream >> current_v3.x >> current_v3.y >> current_v3.z;
				m_points.push_back(current_v3);
				break;
			case cstr2int("vn"):
				l_stream >> current_v3.x >> current_v3.y >> current_v3.z;
				m_normals.push_back(current_v3);
				break;
			case cstr2int("vt"):
				l_stream >> current_v2.x >> current_v2.y;
				m_texcoords.push_back(current_v2);
				break;
			case cstr2int("o"):
			case cstr2int("g"):
				l_stream >> currentMesh;
				m_meshes[currentMesh] = WavefrontMesh();
				break;
			case cstr2int("usemtl"):

				// Get the current material in temp var
				std::string currentMaterialTemp;
				l_stream >> currentMaterialTemp;

				// Get the current mesh that is being processed
				WavefrontMesh & mesh = m_meshes[currentMesh];
				if (mesh.faces.empty() == false)
				{
					currentMesh = currentMesh + currentMaterialTemp;
					m_meshes[currentMesh] = WavefrontMesh();
				}

				currentMaterial = currentMaterialTemp;
				break;
			}

		}

	}

	void WavefrontFile::loadMtl(const std::string & filePath)
	{
		MLOG(filePath);
	}

}