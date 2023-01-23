#ifndef CMeshBuffer_Header
#define CMeshBuffer_Header
#include <glad/glad.h>
#include <cstdint>

#include "CAbstractMeshBuffer.h"

class CAbstractMeshBuffer
{
    GLuint m_VAO;
    GLuint m_bufferID;
    std::uint16_t m_index;
    bool m_isInit;
    class CAbstractMesh* m_abstractMesh;
protected:
    virtual void CustomDestroy()    = 0;
    
    void Init();

    CAbstractMesh* GetParent() const;
public:
    CAbstractMeshBuffer(CAbstractMesh* abstract_mesh, std::uint16_t index);
    virtual void EnableAttribArray()= 0;
    virtual ~CAbstractMeshBuffer() = default;
    void Bind();
    void Destroy();
};

inline CAbstractMesh* CAbstractMeshBuffer::GetParent() const
{
    return m_abstractMesh;
}

inline void CAbstractMeshBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
}

#endif
