#include "impostor_baker.h"

bool TestRenderer::init(const char * vShaderPath, const char * fShaderPath)
{
	
	if (!m_shader.setup(vShaderPath, fShaderPath))
	{
		return false;
	}
	
	initBuffers();

	return true;
}


bool TestRenderer::reload()
{
	return m_shader.reload();
}

bool TestRenderer::render()
{

	float timeValue = glfwGetTime();
	float color = (sin(timeValue) / 2.0f) + 0.5f;

	m_shader.use();
	m_shader.setUniform(color, "green");

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(m_VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3); - without indices
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	m_shader.unuse();

	return true;
}


bool TestRenderer::initBuffers()
{
	float vertices[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom left
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,    // top 
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first triangle
		1, 2, 3    // second triangle
	};

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	return true;
}
