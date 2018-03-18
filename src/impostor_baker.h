#ifndef _IMPSOTOR_BAKER_H_
#define _IMPOSTOR_BAKER_H_

#define  SAFE_ARRAY_DELETE(arr) if(arr){delete[]arr;} arr = nullptr;

#include <string>
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "log.h"
#include "shader.h"

class ImpostorBaker
{
public:
	ImpostorBaker(){}
	~ImpostorBaker(){}
};

class TestRenderer
{
public:
	TestRenderer(){}
	~TestRenderer(){}

	bool init(const char * vShaderPath, const char * fShaderPath);
	bool reload();
	bool render();

private:

	Shader m_shader;

	unsigned int m_VBO = 0;
	unsigned int m_VAO = 0;
	unsigned int m_EBO = 0;

	bool initBuffers();

};


#endif //_IMPOSTOR_BAKER_H_