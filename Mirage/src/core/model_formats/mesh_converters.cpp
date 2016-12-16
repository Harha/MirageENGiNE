#include "mesh_converters.h"

// mirage includes
#include "config.h"
#include "macros.h"
#include "core/model_formats/wavefront_file.h"
#include "core/mesh/mesh_base.h"
#include "core/transform.h"
#include "core/vertex.h"

namespace mirage
{

	std::vector<MeshBase *> convertWavefrontToMeshBase(WavefrontFile * const wfFile)
	{
		if (wfFile == nullptr)
			throw std::exception("mirage::convertWavefrontToMeshBase failed to convert file to BaseMeshes, input file handle points to null.");

		std::vector<MeshBase *> converted;

		// Get the file data into temp references
		auto & points = wfFile->getPoints();
		auto & normals = wfFile->getNormals();
		auto & texcoords = wfFile->getTexcoords();
		auto & meshes = wfFile->getMeshes();
		auto & materials = wfFile->getMaterials();

		// Export vertices from each mesh
		for (auto const & mesh : meshes)
		{
			std::vector<Vertex> vertices;
			std::string name_suffix;

			if (mesh.second.faces.size() > 0)
				name_suffix = mesh.second.faces[0].material;

			for (auto const & face : mesh.second.faces)
			{
				for (size_t i = 0; i < 3; i++)
				{
					glm::vec3 point;
					glm::vec3 normal;
					glm::vec3 tangent;
					glm::vec2 uv;

					point = points[face.points[i]];

					if (mesh.second.hasNormals)
						normal = normals[face.normals[i]];

					if (mesh.second.hasTexcoords)
						uv = texcoords[face.texcoords[i]];

					vertices.push_back(Vertex(point, normal, tangent, uv));
				}
			}

			converted.push_back(new MeshBase(wfFile->getObjFilePath() + ((name_suffix.empty()) ? "" : ("_" + name_suffix)), Transform(), vertices));
		}

		return converted;
	}

}