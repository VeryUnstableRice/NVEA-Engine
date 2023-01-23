#include "CShader.h"
#include <fstream>
#include <memory>
#include <iostream>
#include <string>

inline std::string CShader::GetFileInfo(std::string filepath)
{
	std::ifstream f(filepath);
	std::string output = "", line = "";

	while (std::getline(f, line))
		output += line + "\n";

	return output;
}

unsigned int CShader::numOfShaders = 0;

void CShader::Init(std::string filepath,  GLubyte numOfTextures)
{
	if (m_init) return;
	m_id = ++numOfShaders;
	m_init = 1;

	m_program = glCreateProgram();

	m_frag = MakeShader(filepath + ".fs", GL_FRAGMENT_SHADER);
	m_vert = MakeShader(filepath + ".vs", GL_VERTEX_SHADER);

	glAttachShader(m_program, m_frag);
	glAttachShader(m_program, m_vert);

	glLinkProgram(m_program);
	FindErrors(m_program, true, GL_LINK_STATUS, "[Error]Link Status: \n");

	glDetachShader(m_program, m_frag);
	glDetachShader(m_program, m_vert);

	Use();
	for(int i = 0; i < numOfTextures; ++i)
	{
		std::string textureName = "texture" + std::to_string(i);
		//std::cout << textureName << '\n';
		GLuint tex = glGetUniformLocation(m_program, textureName.c_str());
		glUniform1i(tex, i);
	}
}

void CShader::Use()
{
	if (!m_init) return;
	glUseProgram(m_program);
}

void CShader::SetUniform(glm::mat4 matrix, std::string name)
{
	GLuint id = glGetUniformLocation(m_program, name.c_str());
	//Use();
	glUniformMatrix4fv(id, 1, false, &matrix[0][0]);
}

void CShader::SetUniform(const std::vector<glm::mat4>& matrix, std::string name)
{
	GLuint id = glGetUniformLocation(m_program, name.c_str());
	//Use();
	glUniformMatrix4fv(id, matrix.size(), false, &matrix[0][0][0]);
}

void CShader::SetUniform(glm::vec3 vector, std::string name)
{
	GLuint id = glGetUniformLocation(m_program, name.c_str());
	//Use();
	glUniform3f(id, vector.x, vector.y, vector.z);
}

void CShader::SetUniform(glm::vec4 vector, std::string name)
{
	GLuint id = glGetUniformLocation(m_program, name.c_str());
	//Use();
	glUniform4f(id, vector.x, vector.y, vector.z, vector.w);
}

void CShader::SetUniform(float number, std::string name)
{
	GLuint id = glGetUniformLocation(m_program, name.c_str());
	//Use();
	glUniform1f(id, number);
}

void CShader::SetUniform(int number, std::string name)
{
	GLuint id = glGetUniformLocation(m_program, name.c_str());
	//Use();
	glUniform1i(id, number);
}

CShader::~CShader()
{
	if (m_init) return;

	glDeleteShader(m_vert);
	glDeleteShader(m_frag);
	glDeleteProgram(m_program);
}

GLuint CShader::MakeShader(std::string filepath, GLenum type)
{
	GLuint output = glCreateShader(type);

	std::string source = GetFileInfo(filepath);
	const char* ssource[1] = { source.c_str() };
	glShaderSource(output, 1, ssource, NULL);

	glCompileShader(output);
	FindErrors(output, false, GL_COMPILE_STATUS, filepath);

	return output;
}

void CShader::SetShaderSettings(CShaderSettings* settings)
{
	m_settings = std::move(std::unique_ptr<CShaderSettings>(settings));
	m_settings->SetParent(this);
}

CShaderSettings* CShader::GetShaderSettings() const
{
	return m_settings.get();
}

inline void CShader::FindErrors(GLuint id, bool isProgram, GLenum flag, std::string errorstring)
{
	GLint val;
	if (isProgram)
		glGetProgramiv(id, flag, &val);
	else
		glGetShaderiv(id, flag, &val);

	if (val == GL_FALSE)
	{
		if (isProgram)
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &val);
		else
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &val);

		std::unique_ptr<GLchar[]> ErrorLog = std::make_unique<GLchar[]>(val);
		
		if (isProgram)
			glGetProgramInfoLog(id, val, &val, ErrorLog.get());
		else
			glGetShaderInfoLog(id, val, &val, ErrorLog.get());

		std::cerr << errorstring + "(ShaderError):\n" << &ErrorLog[0];
	}
}
