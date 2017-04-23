#include "gfxengine.h"

// VC++ Weirdness
#define NOMINMAX

// std includes
#include <iostream>

// lib includes
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// mirage includes
#include "config.h"
#include "macros.h"
#include "core/runstate.h"
#include "core/engine.h"
#include "window.h"
#include "graphics/glsl/shader.h"
#include "graphics/camera/camera.h"
#include "core/mesh/mesh_base.h"
#include "graphics/mesh/mesh_renderer.h"
#include "graphics/rendercmd.h"
#include "graphics/glsl/shader.h"
#include "game/game.h"

namespace mirage
{

	GraphicsEngine::GraphicsEngine(CoreEngine * const coreEngine) :
		m_runState(ERS_UNINTIALIZED),
		m_coreEngine(coreEngine),
		m_currentCamera(nullptr),
		m_renderCmds(),
		m_shaderPrograms()
	{

		MLOG_INFO("GraphicsEngine::GraphicsEngine, created.");
	}

	GraphicsEngine::~GraphicsEngine()
	{
		ImGui_ImplGlfwGL3_Shutdown();
	}

	void GraphicsEngine::initialize()
	{
		// Setup GLFW3 / ImGui window binding
		ImGui_ImplGlfwGL3_Init(m_coreEngine->getWindow()->getHandle(), true);

		// Load shader programs
		m_shaderPrograms["model_basic"] = new ShaderProgram("test", "", "basicmesh.vert.glsl", "basicmesh.frag.glsl");

		// Set state to initialized
		m_runState = ERS_INITIALIZED;
		MLOG_INFO("GraphicsEngine::initialize, executed successfully.");
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
			std::vector<MeshRenderer *> meshes = r_cmd->getMeshes();

			program->bind();
			program->setUniformMat4("u_VMatrix", camera->getViewMatrix());
			program->setUniformMat4("u_PMatrix", camera->getProjectionMatrix());

			for (size_t j = 0; j < meshes.size(); j++)
			{
				MeshRenderer * mesh = meshes[j];

				program->setUniformMat4("u_MMatrix", mesh->getTransform()->getModelMatrix());
				program->setUniformVec3("u_col_diffuse", mesh->getMeshBase()->getData()->getMaterial().getColorKd());

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

			MLOG_ERROR("glErrorCheck::glErrorCheck, glGetError(): %s", glErrorStr.c_str());
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

	ShaderProgram * const GraphicsEngine::getShaderProgram(const std::string & name)
	{
		return m_shaderPrograms[name];
	}

}