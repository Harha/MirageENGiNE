#include "gfxengine.h"

// VC++ Weirdness
#define NOMINMAX

// std includes
#include <iostream>
#include <exception>

// lib includes
#include "3rdparty/imgui/imgui.h"
#include "3rdparty/imgui/imgui_impl_glfw_gl3.h"
#include "3rdparty/glad/glad.h"
#include <GLFW/glfw3.h>

// mirage includes
#include "config.h"
#include "macros.h"
#include "core/runstate.h"
#include "core/engine.h"
#include "graphics/window.h"
#include "graphics/camera/camera.h"
#include "graphics/rendercmd.h"
#include "graphics/glsl/shader.h"
#include "core/mesh/mesh_base.h"
#include "graphics/mesh/mesh_renderer.h"
#include "core/material/material_base.h"
#include "graphics/material/texture.h"
#include "game/game.h"

namespace mirage
{

	GraphicsEngine::GraphicsEngine(
		CoreEngine * const coreEngine
	) :
		m_runState(ERS_UNINTIALIZED),
		m_coreEngine(coreEngine),
		m_currentCamera(nullptr),
		m_renderCmds(),
		m_shaderPrograms(),
		m_textureSamplers()
	{
		MLOG_INFO("GraphicsEngine::GraphicsEngine, created.");
	}

	GraphicsEngine::~GraphicsEngine()
	{
		ImGui_ImplGlfwGL3_Shutdown();

		// Deallocate shader programs
		for (auto program_KeyValue : m_shaderPrograms)
		{
			MDELETES(program_KeyValue.second);
		}
	}

	void GraphicsEngine::initialize()
	{
		// Throw if graphics engine run state is not correct
		if (m_runState != ERS_UNINTIALIZED)
		{
			throw std::exception("GraphicsEngine::initialize, m_runState != ERS_UNITIALIZED! Engine run state:" + m_runState);
		}

		// Setup GLFW3 / ImGui window binding
		ImGui_ImplGlfwGL3_Init(m_coreEngine->getWindow()->getHandle(), true);

		// Load shader programs
		m_shaderPrograms["gbuffer"] = new ShaderProgram("gbuffer", "", "basicmesh.vert.glsl", "basicmesh.frag.glsl");

		// Initialize texture samplers
		m_textureSamplers["texture_albedo"] = 0;

		// Set state to initialized
		m_runState = ERS_INITIALIZED;
		MLOG_INFO("GraphicsEngine::initialize, initialized.");
	}

	void GraphicsEngine::render()
	{
		glClearColor(0.33f, 0.33f, 0.33f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//MLOG_DEBUG("Executing RenderCMDs. Size: %zu", m_renderCmds.size());

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CW);

		for (size_t i = 0; i < m_renderCmds.size(); i++)
		{
			// Current render command & data for this command
			RenderCMD * r_cmd = m_renderCmds[i];
			ShaderProgram * program = r_cmd->getProgram();
			Camera * camera = r_cmd->getCamera();
			std::vector<MeshRenderer *> meshes = r_cmd->getMeshRenderers();

			program->bind();
			program->setUniformMat4("u_VMatrix", camera->getViewMatrix());
			program->setUniformMat4("u_PMatrix", camera->getProjectionMatrix());

			for (size_t j = 0; j < meshes.size(); j++)
			{
				MeshRenderer * mesh = meshes[j];

				program->setUniformMat4("u_MMatrix", mesh->getTransform()->getModelMatrix());

				MaterialBase & mesh_material = mesh->getMeshBase()->getData()->getMaterial();

				program->setUniformVec3("u_col_diffuse", mesh_material.getColorDiffuse());

				if (mesh_material.getTextureDiffuse() != nullptr)
				{
					GLenum samplerId = m_textureSamplers["texture_albedo"];
					mesh_material.getTextureDiffuse()->bind(samplerId);
					program->setUniformInt("u_tex_diffuse", static_cast<GLint>(samplerId));
				}


				mesh->render();
			}

			//MLOG_DEBUG("RenderCMD. Camera: %s, Meshes size: %zu", (camera == nullptr) ? "null" : "not null", meshes.size());
		}

		// Deallocate render commands
		for (auto r_cmd : m_renderCmds)
		{
			MDELETES(r_cmd);
		}

		// Clear render commands
		m_renderCmds.clear();

		// Render game GUI (ImGui)
		m_coreEngine->getGame()->renderGUI();

		glErrorCheck();
		glfwSwapBuffers(m_coreEngine->getWindow()->getHandle());
	}

	void GraphicsEngine::glErrorCheck()
	{
		GLenum glError = glGetError();

		if (glError != GL_NO_ERROR)
		{
			std::string glErrorStr;
			switch (glError)
			{
			case GL_INVALID_OPERATION:
				glErrorStr = "GL_INVALID_OPERATION";
				break;
			case GL_INVALID_VALUE:
				glErrorStr = "GL_INVALID_VALUE";
				break;
			case GL_OUT_OF_MEMORY:
				glErrorStr = "GL_OUT_OF_MEMORY";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				glErrorStr = "GL_INVALID_FRAMEBUFFER_OPERATION";
				break;
			default:
				glErrorStr = "GL_UNKNOWN_ERROR (" + std::to_string(glError) + ")";
				break;
			}

			MLOG_ERROR("glErrorCheck::glErrorCheck, error. glGetError(): %s", glErrorStr.c_str());
		}
	}

	void GraphicsEngine::setCurrentCamera(Camera * const camera)
	{
		m_currentCamera = camera;
	}

	Camera * const GraphicsEngine::getCurrentCamera() const
	{
		return m_currentCamera;
	}

	void GraphicsEngine::pushRenderCMD(RenderCMD * const r_cmd)
	{
		m_renderCmds.push_back(r_cmd);
	}

	void GraphicsEngine::clearRenderCMDs()
	{
		// Deallocate render commands
		for (auto r_cmd : m_renderCmds)
		{
			MDELETES(r_cmd);
		}

		// Clear render commands
		m_renderCmds.clear();
	}

	const std::vector<RenderCMD *> & GraphicsEngine::getRenderCMDs() const
	{
		return m_renderCmds;
	}

	void GraphicsEngine::addShaderProgram(const std::string & identifier, ShaderProgram * program)
	{
		auto programs_it = m_shaderPrograms.find(identifier);
		if (programs_it != m_shaderPrograms.end())
		{
			throw std::exception(("GraphicsEngine::addShaderProgram, error. Program with input identifier already exists! Identifier: " + identifier).c_str());
		}

		m_shaderPrograms[identifier] = program;
	}

	void GraphicsEngine::removeShaderProgram(const std::string & identifier)
	{
		MDELETES(m_shaderPrograms[identifier]);
		m_shaderPrograms.erase(identifier);
	}

	ShaderProgram * const GraphicsEngine::getShaderProgram(const std::string & name)
	{
		return m_shaderPrograms[name];
	}

}