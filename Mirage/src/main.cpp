/*
 * Mirage Game Engine
 * Author: Harha
 * (c) 2016-
 */

 // std includes
#include <iostream>
#include <thread>

// lib includes
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include <glm/glm.hpp>

// mirage includes
#include "config.h"
#include "macros.h"
#include "core/engine.h"
#include "core/transform.h"
#include "graphics/vertex.h"
#include "graphics/camera.h"
#include "graphics/window.h"

static void glfwErrorCallback(int error, const char * description)
{
	MERR(description);
}

static void glfwKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	MLOG("Key pressed (key: " << key << ", scancode: " << scancode << ", action: " << action << ")");
}

int main(int argc, char * argv[])
{
	MLOG("Mirage Game Engine, version " << VERSION_STATE << "." << VERSION_MAJOR << "." << VERSION_MINOR);

	// Set glfw error callback function
	glfwSetErrorCallback(glfwErrorCallback);

	// Initialize GLFW3
	if (glfwInit() == GL_FALSE)
	{
		return 1;
	}

	// Create core engine instance
	mirage::CoreEngine * engine = new mirage::CoreEngine("./res/config.ini");

	// Set window callback functions
	glfwSetKeyCallback(engine->getWindow()->getHandle(), glfwKeyCallback);

	// Initialize glad, return error if failed
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == GL_FALSE)
	{
		MDELETES(engine);
		glfwTerminate();
		return 1;
	}

	// Initialize ImGui
	ImGui_ImplGlfwGL3_Init(engine->getWindow()->getHandle(), false);

	glViewport(0, 0, engine->getWindow()->getWidth(), engine->getWindow()->getHeight());

	Transform t;
	t.setScale(glm::vec3(1, 1, 1));

	Vertex testv1;
	MLOG(testv1.getPosition().y);

	glm::vec3 pos;
	glm::quat ori;
	glm::vec3 scl;
	while (glfwWindowShouldClose(engine->getWindow()->getHandle()) == GL_FALSE)
	{
		// Call glfw event callback functions
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();

		// Render some GUI stuff as a test...
		ImGui::Text("Hello, world!");
		ImGui::SliderFloat("tx", &pos.x, -100.0f, 100.0f);
		ImGui::SliderFloat("ty", &pos.y, -100.0f, 100.0f);
		ImGui::SliderFloat("tz", &pos.z, -100.0f, 100.0f);
		ImGui::SliderFloat("ow", &ori.w, -1.0f, 1.0f);
		ImGui::SliderFloat("ox", &ori.x, -1.0f, 1.0f);
		ImGui::SliderFloat("oy", &ori.y, -1.0f, 1.0f);
		ImGui::SliderFloat("oz", &ori.z, -1.0f, 1.0f);
		ImGui::SliderFloat("sx", &scl.x, -10.0f, 10.0f);
		ImGui::SliderFloat("sy", &scl.y, -10.0f, 10.0f);
		ImGui::SliderFloat("sz", &scl.z, -10.0f, 10.0f);
		ori = glm::normalize(ori);
		t.setPosition(pos);
		t.setOrientation(ori);
		t.setScale(scl);
		glm::mat4 tmat = t.getModelMatrix();
		ImGui::Text("%.2f %.2f %.2f %.2f", tmat[0][0], tmat[0][1], tmat[0][2], tmat[0][3]);
		ImGui::Text("%.2f %.2f %.2f %.2f", tmat[1][0], tmat[1][1], tmat[1][2], tmat[1][3]);
		ImGui::Text("%.2f %.2f %.2f %.2f", tmat[2][0], tmat[2][1], tmat[2][2], tmat[2][3]);
		ImGui::Text("%.2f %.2f %.2f %.2f", tmat[3][0], tmat[3][1], tmat[3][2], tmat[3][3]);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		// Rendering
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		glfwSwapBuffers(engine->getWindow()->getHandle());

		// Sleep because why not?
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	// Cleanup resources in correct order
	MDELETES(engine);
	glfwTerminate();

	return 0;
}