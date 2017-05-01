#include "wavefront_file.h"

#pragma warning(disable : 4307)

// std includes
#include <fstream>
#include <regex>
#include <sstream>

// mirage includes
#include "config.h"
#include "macros.h"
#include "util/strutil.h"

namespace mirage
{

	WavefrontFile::WavefrontFile(const std::string & filePath) :
		m_objFilePath(filePath),
		m_mtlFilePath("NULL"),
		m_points(),
		m_normals(),
		m_texcoords(),
		m_meshes(),
		m_materials()
	{
		loadObj(m_objFilePath);
	}

	WavefrontFile::~WavefrontFile()
	{
		MLOG_INFO("WavefrontFile::~WavefrontFile, destroyed. FilePath: %s", m_objFilePath.c_str());
	}

	void WavefrontFile::loadObj(const std::string & filePath)
	{
		MLOG_INFO("WavefrontFile::loadObj, attempting to load (%s) into memory...", filePath.c_str());

		// Read the file into memory
		std::ifstream file(filePath);

		// Throw if the file didn't open
		if (file.is_open() == false)
		{
			throw std::exception("WavefrontFile::loadObj, failed to open target .obj file, make sure it exists.");
		}

		// Loading process related variables
		std::string mesh_current = "root";
		std::string material_current = "root";
		glm::vec3 vec3_current;
		glm::vec2 vec2_current;

		// Initialize current mesh
		m_meshes[mesh_current] = WavefrontMesh();
		m_meshes[mesh_current].mesh_identifier = mesh_current;
		m_meshes[mesh_current].material_identifier = material_current;

		// Iterate through every line
		std::string l;
		while (std::getline(file, l))
		{
			// Trim any leading/trailing/extra ws
			l.erase(std::unique(l.begin(), l.end(), istwospace), l.end());

			// Line sstream
			std::istringstream l_stream(l);

			// Get the type of the current line
			std::string type;
			l_stream >> type;

			switch (cstr2int(type.c_str()))
			{
			case cstr2int("mtllib"):
			{
				l_stream >> m_mtlFilePath;
				m_mtlFilePath = filetofilepath(m_objFilePath) + m_mtlFilePath;
				loadMtl(m_mtlFilePath);
			} break;
			case cstr2int("v"):
			{
				l_stream >> vec3_current.x >> vec3_current.y >> vec3_current.z;
				m_points.push_back(vec3_current);
			} break;
			case cstr2int("vn"):
			{
				l_stream >> vec3_current.x >> vec3_current.y >> vec3_current.z;
				m_normals.push_back(vec3_current);
			} break;
			case cstr2int("vt"):
			{
				l_stream >> vec2_current.x >> vec2_current.y;
				m_texcoords.push_back(vec2_current);
			} break;
			case cstr2int("o"):
			case cstr2int("g"):
			{
				// Save last mesh identifier temporarily
				std::string mesh_last(mesh_current);

				// Set next mesh identifier as current mesh & instantiate it
				l_stream >> mesh_current;
				m_meshes[mesh_current] = WavefrontMesh();
				m_meshes[mesh_current].mesh_identifier = mesh_current;

				// Set current mesh identifier for this mesh
				m_meshes[mesh_current].mesh_identifier = mesh_current;

				// Set current material identifier for this mesh
				m_meshes[mesh_current].material_identifier = material_current;

				MLOG_DEBUG("WavefrontFile::loadObj, g. mesh_last: %s, faces: %zu, vertices: %zu, mesh_current: %s", mesh_last.c_str(), m_meshes[mesh_last].faces.size(), m_meshes[mesh_last].faces.size() * 3, mesh_current.c_str());
			} break;
			case cstr2int("usemtl"):
			{
				// Set next material identifier as current
				l_stream >> material_current;

				// Get the current mesh that is being processed
				// and split the mesh into two if it had faces, this handles multiple materials + non-consistent mesh objects
				WavefrontMesh & mesh = m_meshes[mesh_current];
				if (mesh.faces.empty() == false)
				{
					mesh_current = mesh_current + material_current;
					m_meshes[mesh_current] = WavefrontMesh();

					// Set current mesh identifier for this mesh
					m_meshes[mesh_current].mesh_identifier = mesh_current;
				}

				// Set current material identifier for this mesh
				m_meshes[mesh_current].material_identifier = material_current;
			} break;
			case cstr2int("f"):
			{
				// Initially create the face with current material
				WavefrontFace face;
				bool hasNormals = false;
				bool hasTexcoords = false;

				// Determine face format, v1/t1/n1 format(s) first
				if (l.find("//") == std::string::npos)
				{
					// Count the number of values on this line
					int n = std::count_if(l.begin(), l.end(), [](unsigned char c) { return c == '/'; });

					// Replace slashes with whitespace & create sstream
					std::replace(l.begin(), l.end(), '/', ' ');
					std::istringstream lf(l.substr(2));

					// v1/t1/n1
					if (n == 6)
					{
						lf >> face.points[0];
						lf >> face.texcoords[0];
						lf >> face.normals[0];

						lf >> face.points[1];
						lf >> face.texcoords[1];
						lf >> face.normals[1];

						lf >> face.points[2];
						lf >> face.texcoords[2];
						lf >> face.normals[2];

						hasNormals = true;
						hasTexcoords = true;
					}
					// v1/t1
					else if (n == 3)
					{
						lf >> face.points[0];
						lf >> face.texcoords[0];

						lf >> face.points[1];
						lf >> face.texcoords[1];

						lf >> face.points[2];
						lf >> face.texcoords[2];

						hasTexcoords = true;
					}
					// v1
					else
					{
						lf >> face.points[0];
						lf >> face.points[1];
						lf >> face.points[2];
					}
				}
				// v1//n1 format(s)
				else
				{
					// Replace slashes with whitespace & create sstream
					std::replace(l.begin(), l.end(), '/', ' ');
					std::istringstream lf(l.substr(2));

					// Save the face information
					lf >> face.points[0];
					lf >> face.normals[0];

					lf >> face.points[1];
					lf >> face.normals[1];

					lf >> face.points[2];
					lf >> face.normals[2];

					hasNormals = true;
				}

				// Correct the face indices
				face.points[0]--;
				face.points[1]--;
				face.points[2]--;

				if (hasNormals == true)
				{
					face.normals[0]--;
					face.normals[1]--;
					face.normals[2]--;
				}

				if (hasTexcoords == true)
				{
					face.texcoords[0]--;
					face.texcoords[1]--;
					face.texcoords[2]--;
				}

				// Get the pointer to current mesh in map
				WavefrontMesh * mesh = &m_meshes[mesh_current];

				// Create the mesh if it doesn't exist & set mesh / material identifiers
				if (mesh == nullptr)
				{
					m_meshes[mesh_current] = WavefrontMesh();
					m_meshes[mesh_current].mesh_identifier = mesh_current;
					m_meshes[mesh_current].material_identifier = material_current;
				}

				// Set few flags
				m_meshes[mesh_current].hasNormals = hasNormals;
				m_meshes[mesh_current].hasTexcoords = hasTexcoords;

				// Insert the face
				m_meshes[mesh_current].faces.push_back(face);
			} break;
			}
		}

		MLOG_INFO("WavefrontFile::loadObj, loaded successfully. Mesh count: %d", m_meshes.size());
	}

	void WavefrontFile::loadMtl(const std::string & filePath)
	{
		MLOG_INFO("WavefrontFile::loadMtl, attempting to load (%s) into memory...", filePath.c_str());

		// Read the file into memory
		std::ifstream file(filePath);

		// Throw if the file didn't open
		if (file.is_open() == false)
		{
			throw std::exception("WavefrontFile::loadMtl, failed to open target .mtl file, make sure it exists.");
		}

		// Loading process related variables
		std::string material_current = "root";

		// Intialize current material
		m_materials[material_current] = WavefrontMaterial();

		// Iterate through every line
		std::string l;
		while (std::getline(file, l))
		{
			// Trim any leading/trailing/extra ws
			l.erase(std::unique(l.begin(), l.end(), istwospace), l.end());

			// Line sstream
			std::istringstream l_stream(l);

			// Get the type of the current line
			std::string type;
			l_stream >> type;

			switch (cstr2int(type.c_str()))
			{
			case cstr2int("newmtl"):
			{
				// Save last material identifier temporarily
				std::string material_last(material_current);

				// Set next material identifier as current mesh & instantiate it
				l_stream >> material_current;
				m_materials[material_current] = WavefrontMaterial();

				MLOG_DEBUG("WavefrontFile::loadMtl, newmtl. material_last: %s, material_current: %s", material_last.c_str(), material_current.c_str());
			} break;
			case cstr2int("illum"):
			{
				l_stream >> m_materials[material_current].illum;
			} break;
			case cstr2int("map_Kd"):
			{
				std::getline(l_stream, m_materials[material_current].KdTex);
				trim(m_materials[material_current].KdTex);
				m_materials[material_current].KdTex = filetofilepath(m_mtlFilePath) + m_materials[material_current].KdTex;
			} break;
			case cstr2int("map_Ks"):
			{
				std::getline(l_stream, m_materials[material_current].KsTex);
				trim(m_materials[material_current].KsTex);
				m_materials[material_current].KsTex = filetofilepath(m_mtlFilePath) + m_materials[material_current].KsTex;
			} break;
			case cstr2int("map_Ke"):
			{
				std::getline(l_stream, m_materials[material_current].KeTex);
				trim(m_materials[material_current].KeTex);
				m_materials[material_current].KeTex = filetofilepath(m_mtlFilePath) + m_materials[material_current].KeTex;
			} break;
			case cstr2int("Ka"):
			{
				l_stream >> m_materials[material_current].Ka.r;
				l_stream >> m_materials[material_current].Ka.g;
				l_stream >> m_materials[material_current].Ka.b;
			} break;
			case cstr2int("Kd"):
			{
				l_stream >> m_materials[material_current].Kd.r;
				l_stream >> m_materials[material_current].Kd.g;
				l_stream >> m_materials[material_current].Kd.b;
			} break;
			case cstr2int("Ks"):
			{
				l_stream >> m_materials[material_current].Ks.r;
				l_stream >> m_materials[material_current].Ks.g;
				l_stream >> m_materials[material_current].Ks.b;
			} break;
			case cstr2int("Ke"):
			{
				l_stream >> m_materials[material_current].Ke.r;
				l_stream >> m_materials[material_current].Ke.g;
				l_stream >> m_materials[material_current].Ke.b;
			} break;
			case cstr2int("Ns"):
			{
				l_stream >> m_materials[material_current].Ns;
			} break;
			case cstr2int("Ni"):
			{
				l_stream >> m_materials[material_current].Ni;
			} break;
			case cstr2int("Fr"):
			{
				l_stream >> m_materials[material_current].Ni;
			} break;
			}
		}

		MLOG_INFO("WavefrontFile::loadMtl, loaded successfully. Material count: %d", m_materials.size());
	}

	std::string WavefrontFile::getObjFilePath() const
	{
		return m_objFilePath;
	}

	std::string WavefrontFile::getMtlFilePath() const
	{
		return m_mtlFilePath;
	}

	std::vector<glm::vec3> & WavefrontFile::getPoints()
	{
		return m_points;
	}

	std::vector<glm::vec3> & WavefrontFile::getNormals()
	{
		return m_normals;
	}

	std::vector<glm::vec2> WavefrontFile::getTexcoords()
	{
		return m_texcoords;
	}

	std::map<std::string, WavefrontMesh> & WavefrontFile::getMeshes()
	{
		return m_meshes;
	}

	std::map<std::string, WavefrontMaterial> & WavefrontFile::getMaterials()
	{
		return m_materials;
	}

}