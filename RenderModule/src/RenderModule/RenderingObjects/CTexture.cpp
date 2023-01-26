#include "CTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

#include "RenderModule/Camera/CCameraBuffer.h"

CTexture::~CTexture()
{
	Clear();
}

void CTexture::Init(std::string filepath)
{
	unsigned char* data = stbi_load(filepath.c_str(), &m_width, &m_height, nullptr, STBI_rgb_alpha);

	if (!data) std::cerr << "Invalid path: " + filepath;
	InitData(data, GL_RGBA, m_width, m_height);

	stbi_image_free(data);
}

void CTexture::InitData(unsigned char* data, GLenum mode, int width, int height, GLenum type)
{
	Clear();
	glActiveTexture(GL_TEXTURE0);

	glGenTextures(1, &m_tex);
	glBindTexture(GL_TEXTURE_2D, m_tex);

	glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, type, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	m_init = true;
}

void CTexture::AttachToBuffer(CCameraBuffer* camera_buffer, GLenum type)
{
	Clear();
	glGenTextures(1, &m_tex);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	
	ReallocateSize(camera_buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, camera_buffer->m_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, type, GL_TEXTURE_2D, m_tex, 0); 
	m_init = true;
}

void CTexture::ReallocateSize(CCameraBuffer* camera_buffer)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, camera_buffer->m_width, camera_buffer->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
}

void CTexture::Clear()
{
	if (!m_init) return;
	glDeleteTextures(1, &m_tex);
	m_init = false;
}

void CTexture::Bind()
{
	if (!m_init) return;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_tex);
}

int CTexture::GetWidth()
{
	return m_width;
}

int CTexture::GetHeight()
{
	return m_height;
}

const GLuint& CTexture::getGLID() const
{
	return m_tex;
}