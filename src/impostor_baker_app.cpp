#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "log.h"

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		fprintf_s(stderr, "Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fprintf_s(stderr, "Failed to initialize GLAD\n");
		return -1;
	}

	// main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

#define ololo(l) if ((l) >= Log::level()){printf("im here");}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Log_debug("Got change size callback; width %d, height %d", width, height);

	glViewport(0, 0, width, height);
}