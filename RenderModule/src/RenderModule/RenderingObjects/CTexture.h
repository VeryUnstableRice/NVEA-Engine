#ifndef CTEXTURE_HEADER
#define CTEXTURE_HEADER
#include <string>

#include "Engine/Object/CObject.h"
#include "glad/glad.h"

class CTexture : public CObject
{
	bool m_init = false;
	GLuint m_tex;
	GLint m_width, m_height;
	void AttachToBuffer(class CCameraBuffer* camera_buffer, GLenum type = GL_COLOR_ATTACHMENT0);
	void ReallocateSize(class CCameraBuffer* camera_buffer);
	friend class CCameraBuffer;	
public:
	virtual ~CTexture();
	
	void Init(std::string filepath);
	void InitData(unsigned char* data, GLenum mode, int width, int height, GLenum type = GL_UNSIGNED_BYTE);
	void Clear();
	
	void Bind();
	const GLuint& getGLID() const;
	int GetWidth();
	int GetHeight();
};

#endif // !CTEXTURE_HEADER
