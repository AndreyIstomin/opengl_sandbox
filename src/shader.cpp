#include "shader.h"

bool Shader::setup(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	m_vShaderPath = "";
	m_fShaderPath = "";

	if (vertexPath)
	{
		m_vShaderPath = std::string(vertexPath);
	}

	if (fragmentPath)
	{
		m_fShaderPath = std::string(fragmentPath);
	}

	return reload();
}

bool Shader::reload()
{
	unsigned int vShader, fShader;
	std::string vShaderSrc, fShaderSrc;
	char log[512];

	if (m_vShaderPath != "")
	{
		if (!loadShader(vShaderSrc, m_vShaderPath.c_str()))
		{
			Log_error("failed to load vertex shader from %s", m_vShaderPath);
			return false;
		}

		if (!compileShader(vShader, vShaderSrc, GL_VERTEX_SHADER, log))
		{
			Log_error("vertex shader compile error: %s", log);
			return false;
		}
	}


	if (m_fShaderPath != "")
	{
		if (!loadShader(fShaderSrc, m_fShaderPath.c_str()))
		{
			Log_error("failed to load fragment shader from %s", m_fShaderPath);
			return false;
		}

		if (!compileShader(fShader, fShaderSrc, GL_FRAGMENT_SHADER, log))
		{
			Log_error("fragment shader compile error: %s", log);
			return false;
		}
	}


	m_shaderProgram = glCreateProgram();
	if (m_vShaderPath != "")
	{
		glAttachShader(m_shaderProgram, vShader);
	}

	if (m_fShaderPath != "")
	{
		glAttachShader(m_shaderProgram, fShader);
	}
	glLinkProgram(m_shaderProgram);

	int success;
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, log);
		Log_error("Program error: %s", log);
		return false;
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return true;
}

bool Shader::loadShader(std::string & shaderSrc, const GLchar * path)
{
	std::stringstream ss;
	std::ifstream is;
	is.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		is.open(path);
		ss << is.rdbuf();
		shaderSrc = ss.str();
	}
	catch (std::ifstream::failure e)
	{
		Log_error("File read exception, code %d, %s", e.code(), e.what());
		return false;
	}

	return true;
}

bool Shader::compileShader(unsigned int & shader, std::string & shaderSrc, unsigned int shaderType, char * infoLog)
{

	const char * src = shaderSrc.c_str();
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	int  success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		return false;
	}

	return true;
}

bool Shader::setUniform(float value, const char * name)
{
	int location = glGetUniformLocation(m_shaderProgram, name);
	if (location == -1)
	{
		Log_error("failed to found uniform \"%s\"", name);
		return false;
	}
	glUniform1f(location, value);

	return true;
}