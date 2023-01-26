#include "CRenderBuffer.h"

#include "RenderModule/Camera/CCameraBuffer.h"

void CRenderBuffer::Clear()
{
    if(!m_init) return;
    glDeleteRenderbuffers(1, &m_rbo);
    m_init = false;
}

void CRenderBuffer::AttachToBuffer(CCameraBuffer* camera_buffer, GLenum type, GLenum storageType)
{
    Clear();
    glGenRenderbuffers(1, &m_rbo);
    ReallocateSize(camera_buffer, type);
    glBindFramebuffer(GL_FRAMEBUFFER, camera_buffer->m_fbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
    m_init = true;
}

void CRenderBuffer::ReallocateSize(CCameraBuffer* camera_buffer, GLenum type)
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, camera_buffer->m_width, camera_buffer->m_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
