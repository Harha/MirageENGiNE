#include "mesh_converters.h"

// mirage includes
#include "config.h"
#include "macros.h"
#include "core/model_formats/wavefront_file.h"
#include "core/mesh/mesh_base.h"
#include "graphics/mesh/mesh_renderer.h"
#include "core/material/material_base.h"
#include "core/transform.h"
#include "core/vertex.h"

namespace mirage
{

	std::vector<MeshBase *> convert_wavefront_to_basemesh(WavefrontFile * const wfFile)
	{
		if (wfFile == nullptr)
			throw std::exception("mirage::convertWavefrontToMeshBase failed to convert file to base meshes, input file handle points to null.");

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
			std::string mesh_str;
			std::string material_str;

			if (mesh.second.faces.size() > 0)
				name_suffix = mesh.second.faces[0].material;

			// Parse face data
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

				mesh_str = face.mesh;
				material_str = face.material;
			}

			// Parse material data
			MaterialBase material;
			auto materials_it = materials.find(material_str);
			if (materials_it != materials.end())
			{
				// Get the wavefront material object
				auto material_wff = materials_it->second;

				// Transfer values from wavefront material to base material
				material.setColorKd(glm::vec3(material_wff.Kd.r, material_wff.Kd.g, material_wff.Kd.b));
				material.setColorKs(glm::vec3(material_wff.Ks.r, material_wff.Ks.g, material_wff.Ks.b));
			}

			// Only convert current mesh if it contains vertex data
			if (vertices.size() > 0)
			{
				converted.push_back(
					new MeshBase(
						wfFile->getObjFilePath() + ((name_suffix.empty()) ? "" : ("_" + name_suffix)),
						vertices,
						material
					)
				);

				MLOG_DEBUG("convert_wavefront_to_basemesh, object: %s vertices: %zu", mesh_str.c_str(), vertices.size());
			}

		}

		return converted;
	}

	void convert_wavefront_to_all(
		WavefrontFile * const wfFile,
		std::vector<MeshBase *> & out_base,
		std::vector<MeshRenderer *> & out_renderer
	)
	{
		// First, convert to base meshes
		out_base = convert_wavefront_to_basemesh(wfFile);

		// Then, convert to mesh renderers
		for (size_t i = 0; i < out_base.size(); i++)
		{
			out_renderer.push_back(new MeshRenderer(out_base[i]));

			MLOG_DEBUG("convert_wavefront_to_meshrenderer");
		}
	}

}