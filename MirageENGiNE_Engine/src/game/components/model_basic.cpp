#include "model_basic.h"

// std includes
#include <exception>
#include <stdexcept>

// lib includes
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// mirage includes
#include "macros.h"
#include "util/strutil.h"
#include "graphics/gfxengine.h"
#include "game/gobject.h"
#include "core/mesh/mesh_base.h"
#include "graphics/mesh/mesh_renderer.h"
#include "graphics/rendercmd.h"
#include "core/model_formats/wavefront_file.h"
#include "core/model_formats/mesh_converters.h"

namespace mirage
{

	ModelBasic::ModelBasic(
		const std::string & filePath,
		const std::string & identifier
	) :
		GameComponent(GC_MODEL_BASIC, identifier),
		m_filePath("./data/models/" + filePath),
		m_meshBases(),
		m_meshRenderers()
	{
		// Throw if input file extension is not supported
		std::string fileExtension = filetoextension(m_filePath);
		if (fileExtension != "obj")
		{
			throw std::runtime_error("ModelBasic::ModelBasic, error. Input file extension is not supported! Supported extensions: .obj");
		}

		// Load mesh data in chosen format
		WavefrontFile * w_file = new WavefrontFile(m_filePath);

		// Convert loaded mesh data into engine mesh objects
		convert_wavefront_to_all(w_file, true, m_meshBases, m_meshRenderers);

		// Deallocate the original mesh data
		MDELETES(w_file);
	}

	ModelBasic::~ModelBasic()
	{
		// Deallocate mesh renderers
		for (auto mesh_renderer : m_meshRenderers)
		{
			MDELETES(mesh_renderer);
		}

		// Deallocate base meshes
		for (auto mesh_base : m_meshBases)
		{
			MDELETES(mesh_base);
		}
	}

	void ModelBasic::update(float dt)
	{

	}

	void ModelBasic::render(GraphicsEngine * const gfxEngine)
	{
		RenderCMD * r_cmd = new RenderCMD(gfxEngine->getShaderProgram("gbuffer"), gfxEngine->getCurrentCamera(), m_meshRenderers);
		gfxEngine->pushRenderCMD(r_cmd);
	}

	void ModelBasic::setParent(GameObject * const parent)
	{
		m_parent = parent;

		for (auto mesh_base : m_meshBases)
		{
			mesh_base->setTransform(&m_parent->getTransform());
		}
	}

	const std::string & ModelBasic::getFilePath() const
	{
		return m_filePath;
	}

	const std::vector<MeshBase *> & ModelBasic::getMeshBases() const
	{
		return m_meshBases;
	}

	const std::vector<MeshRenderer *> & ModelBasic::getMeshRenderers() const
	{
		return m_meshRenderers;
	}

}