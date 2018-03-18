#ifndef _IMPOSTOR_BAKER_APP_H_
#define _IMPOSTOR_BAKER_APP_H_

#include <GLFW/glfw3.h>
#include "impostor_baker.h"

class ImpostorBakerApp
{
public:
	ImpostorBakerApp(){};
	~ImpostorBakerApp(){};

	bool run();

private:

	GLFWwindow * m_window = nullptr;
	TestRenderer m_renderer;

	void processInput();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

};

#endif // _IMPOSTOR_BAKER_APP_H_