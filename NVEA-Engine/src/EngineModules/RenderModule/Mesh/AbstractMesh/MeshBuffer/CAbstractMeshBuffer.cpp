#include "CAbstractMeshBuffer.h"

#include "EngineModules/RenderModule/Mesh/AbstractMesh/CAbstractMesh.h"


CAbstractMeshBuffer::CAbstractMeshBuffer(CAbstractMesh* abstract_mesh, std::uint16_t index) : m_index(index), m_abstractMesh(abstract_mesh)
{
    
}

void CAbstractMeshBuffer::Init()
{
    Destroy();
    m_isInit = true;
    m_abstractMesh->BingVAO();
    glGenBuffers(1, &m_bufferID);
}

void CAbstractMeshBuffer::Destroy()
{
    if(!m_isInit) return;
    m_isInit = false;
    m_abstractMesh->BingVAO();
    glDeleteBuffers(0, &m_bufferID);
    CustomDestroy();
}
