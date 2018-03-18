#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cstdio>

#include "log.h"
#include "impostor_baker_app.h"

#define SCR_WIDTH 800
#define SCR_HEIGHT 600


int main()
{
	ImpostorBakerApp app;
	if (!app.run())
	{
		std::getchar();
		return -1;
	}

	std::getchar();
	return 0;
}


void ImpostorBakerApp::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Log_debug("Got change size callback; width %d, height %d", width, height);

	glViewport(0, 0, width, height);
}


void ImpostorBakerApp::processInput()
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_window, true);
	}

	static bool rAlreadyPressed = false;
	if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS)
	{
		if (!rAlreadyPressed)
		{
			m_renderer.reload();
			Log_info("setup test renderer program");
			rAlreadyPressed = true;
		}
	}
	else
	{
		rAlreadyPressed = false;
	}
}


bool ImpostorBakerApp::run()
{
	Log::setLevel(Log::DEBUG);

	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	m_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (m_window == NULL)
	{
		Log_error("Failed to create GLFW window\n");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, &(ImpostorBakerApp::framebuffer_size_callback));


	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Log_error("failed to initialize GLAD\n");
		return false;
	}

	m_renderer = TestRenderer();
	if (!m_renderer.init("src/test_render_vertex.glsl", "src/test_render_fragment.glsl"))
	{
		Log_error("failed to init test renderer");
		return false;
	}

	// main loop
	while (!glfwWindowShouldClose(m_window))
	{
		// input
		processInput();

		// render here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_renderer.render();


		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	glfwTerminate();

	return true;
}
