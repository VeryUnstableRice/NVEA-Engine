#ifndef CSHADER_HEADER
#define CSHADER_HEADER
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "Engine/Object/CObject.h"


class CShaderSettings
{
	class CShader* m_parent = nullptr;
protected:
	CShader* GetParent() const { return m_parent;};
public:
	virtual void UpdateUniforms(class CCameraEntity* camera) {};
	void SetParent(CShader* parent) {
		m_parent = parent;
		} 
};

class CShader : public CObject
{
	inline std::string GetFileInfo(std::string filepath);
	inline GLuint MakeShader(std::string filepath, GLenum type);
	inline void FindErrors(GLuint id, bool isProgram, GLenum flag, std::string errorstring);
	bool m_init = false;
	GLuint m_program, m_frag, m_vert;
	static unsigned int numOfShaders;
	unsigned int m_id;
	std::unique_ptr<CShaderSettings> m_settings = nullptr;
public:
	void Init(std::string filepath, GLubyte numOfTextures = 2);

	void Use();
	void SetUniform(glm::mat4 matrix, std::string name);
	void SetUniform(const std::vector<glm::mat4>& matrix, std::string name);
	void SetUniform(glm::vec3 vector, std::string name);
	void SetUniform(glm::vec4 vector, std::string name);
	void SetUniform(int number, std::string name);
	void SetUniform(float number, std::string name);

	void SetShaderSettings(CShaderSettings* settings);
	CShaderSettings* GetShaderSettings() const;

	~CShader();
};

#endif