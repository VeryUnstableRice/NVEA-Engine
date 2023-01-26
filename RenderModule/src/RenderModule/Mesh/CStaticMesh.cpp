#include "CStaticMesh.h"

#include "AbstractMesh/MeshBuffer/CTemplateMeshBuffer.h"

void CStaticMesh::GenerateBuffers()
{
    CAbstractMesh::GenerateBuffers();
    m_vertexBuffer = MakeBuffer<CVector3MeshBuffer<0>>();
    m_textureBuffer = MakeBuffer<CVector2MeshBuffer<1>>();
}

void CStaticMesh::Generate(const std::vector<EngineMath::SVector3f>& VertexBuffer, const std::vector<EngineMath::SVector2f>& TexCoords)
{
    Init();
    m_indices = (GLuint)VertexBuffer.size();
    //CAbstractEngine::Engine->PrintLog("Created static mesh with: " + std::to_string(m_indices) + "(indices)", GL_LOG);
    m_vertexBuffer->Initialize(VertexBuffer);
    m_textureBuffer->Initialize(TexCoords);
}
