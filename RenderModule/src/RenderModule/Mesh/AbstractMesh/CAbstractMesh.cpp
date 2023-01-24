#include "CAbstractMesh.h"
#include <glad/glad.h>

#include "MeshBuffer/CAbstractMeshBuffer.h"
#include <Engine/CAbstractEngine.h>

void CAbstractMesh::GenerateBuffers()
{
    
}

CAbstractMesh::CAbstractMesh() : CObject()
{
}

CAbstractMesh::~CAbstractMesh()
{
    Clear();
}

void CAbstractMesh::Init()
{
    Clear();
    glCreateVertexArrays(1, &m_VAO);
    BingVAO();
    
    GenerateBuffers();
    m_isInit = true;
}

void CAbstractMesh::Clear()
{
    if (!m_isInit) return;
    glDeleteVertexArrays(1, &m_VAO);
    for(std::shared_ptr<CAbstractMeshBuffer>& buffer : m_meshBuffers)
        buffer->Destroy();
    m_isInit = false;
}

void CAbstractMesh::BingVAO()
{
    glBindVertexArray(m_VAO);
}

void CAbstractMesh::Render(GLenum type)
{
    if (!IsInitialized()) return;
    
    BingVAO();
    for(std::shared_ptr<CAbstractMeshBuffer>& mesh : m_meshBuffers)
        mesh->EnableAttribArray();
    glDrawArrays( type, 0, m_indices);
}
