#ifndef CStaticMesh_HEADER
#define CStaticMesh_HEADER
#include "AbstractMesh/CAbstractMesh.h"
#include "AbstractMesh/MeshBuffer/CTemplateMeshBuffer.h"

class CStaticMesh : public CAbstractMesh
{
    CVector3MeshBuffer<0> *m_vertexBuffer = nullptr;
    CVector2MeshBuffer<1> *m_textureBuffer = nullptr;
protected:
    void GenerateBuffers() override;
public:
    void Generate(const std::vector<EngineMath::SVector3f>& VertexBuffer, const std::vector<EngineMath::SVector2f>& TexCoords);
};
#endif
