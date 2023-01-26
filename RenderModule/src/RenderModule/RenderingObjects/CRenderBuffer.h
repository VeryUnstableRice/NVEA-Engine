#ifndef CRenderBuffer_Header
#define CRenderBuffer_Header
#include <glad/glad.h>

#include "Engine/Object/CObject.h"

class CRenderBuffer : public CObject
{
    GLuint m_rbo;

    bool m_init = false;

    void Clear();
public:
    void AttachToBuffer(class CCameraBuffer* camera_buffer, GLenum type, GLenum storageType); // GL_DEPTH_STENCIL_ATTACHMENT
    void ReallocateSize(class CCameraBuffer* camera_buffer, GLenum type); // GL_DEPTH24_STENCIL8
};

#endif