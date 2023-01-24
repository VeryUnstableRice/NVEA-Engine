#ifndef CStaticMesh_HEADER
#define CStaticMesh_HEADER
#include "AbstractMesh/CAbstractMesh.h"
#include "AbstractMesh/MeshBuffer/CTemplateMeshBuffer.h"

class CStaticMesh : public CAbstractMesh
{
    CVector3MeshBuffer<0> *m_vertexBuffer = nullptr;
protected:
    void GenerateBuffers() override;
public:
    void Generate(const std::vector<EngineMath::SVector3f>& VertexBuffer);
};
#endif
