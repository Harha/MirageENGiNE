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

	std::vector<MeshBase *> convert_wavefront_to_basemesh(WavefrontFile * const wfFile, bool erase_wfFile)
	{
		// Throw if input file is null
		if (wfFile == nullptr)
		{
			throw std::exception("mirage::convert_wavefront_to_basemesh, failed. Cannot convert file to base meshes, input file handle points to null.");
		}

		std::vector<MeshBase *> converted;

		// Get the file data into temp references
		auto & wf_points = wfFile->getPoints();
		auto & wf_normals = wfFile->getNormals();
		auto & wf_texcoords = wfFile->getTexcoords();
		auto & wf_meshes = wfFile->getMeshes();
		auto & wf_materials = wfFile->getMaterials();

		// Import vertices & materials for each mesh & then export as internal mesh objects
		for (auto const & mesh_it : wf_meshes)
		{
			// Conversion process related variables
			auto & wf_mesh = mesh_it.second;
			MaterialBase material;
			std::vector<Vertex> vertices;

			// Parse each face
			for (auto const & face : wf_mesh.faces)
			{
				for (size_t i = 0; i < 3; i++)
				{
					// Face data
					glm::vec3 point;
					glm::vec3 normal;
					glm::vec3 tangent;
					glm::vec2 uv;

					point = wf_points[face.points[i]];

					if (wf_mesh.hasNormals)
						normal = wf_normals[face.normals[i]];

					if (wf_mesh.hasTexcoords)
						uv = wf_texcoords[face.texcoords[i]];

					vertices.push_back(Vertex(point, normal, tangent, uv));

					// Clear the data of this face to free memory, could be useful when loading HUGE meshes
					if (erase_wfFile)
					{
						wf_points.erase(wf_points.begin() + face.points[i], wf_points.begin() + face.points[i]);

						if (wf_mesh.hasNormals)
							wf_normals.erase(wf_normals.begin() + face.normals[i], wf_normals.begin() + face.normals[i]);

						if (wf_mesh.hasTexcoords)
							wf_texcoords.erase(wf_texcoords.begin() + face.texcoords[i], wf_texcoords.begin() + face.texcoords[i]);
					}
				}
			}

			// Skip this mesh if no vertices available
			if (vertices.size() <= 0)
			{
				MLOG_WARNING("mirage::convert_wavefront_to_basemesh, skipped. Object: %s", wf_mesh.mesh_identifier.c_str());

				continue;
			}

			// Parse material
			WavefrontMaterial * wf_material = &wf_materials[wf_mesh.material_identifier];
			if (wf_material != nullptr)
			{
				// Assign material data
				material.setColorDiffuse(glm::vec3(wf_material->Kd.r, wf_material->Kd.g, wf_material->Kd.b));
				material.setColorSpecular(glm::vec3(wf_material->Ks.r, wf_material->Ks.g, wf_material->Ks.b));
			}

			// Do the conversion
			std::string file_path = wfFile->getObjFilePath() + wf_mesh.mesh_identifier;
			converted.push_back(new MeshBase(file_path, vertices, material));

			MLOG_DEBUG("mirage::convert_wavefront_to_basemesh, converted. Object: %s, vertices: %zu", wf_mesh.mesh_identifier.c_str(), vertices.size());

			// Clear the data of this mesh to free memory, could be useful when loading HUGE meshes
			if (erase_wfFile)
			{
				wf_meshes.erase(wf_mesh.mesh_identifier);
			}
		}

		return converted;
	}

	void convert_wavefront_to_all(
		WavefrontFile * const wfFile,
		bool erase_wfFile,
		std::vector<MeshBase *> & out_base,
		std::vector<MeshRenderer *> & out_renderer
	)
	{
		// Throw if input file is null
		if (wfFile == nullptr)
		{
			throw std::exception("mirage::convert_wavefront_to_all, failed. Cannot convert file to base meshes, input file handle points to null.");
		}

		// First, convert to base meshes
		out_base = convert_wavefront_to_basemesh(wfFile, erase_wfFile);

		// Then, convert to mesh renderers
		for (size_t i = 0; i < out_base.size(); i++)
		{
			out_renderer.push_back(new MeshRenderer(out_base[i]));

			MLOG_DEBUG("mirage::convert_wavefront_to_all, converted. Index: %zu", i);
		}
	}

}