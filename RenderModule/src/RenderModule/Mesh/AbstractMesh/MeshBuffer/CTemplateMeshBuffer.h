#ifndef CTemplateMeshBuffer_Header
#define CTemplateMeshBuffer_Header

#include "CAbstractMeshBuffer.h"
#include "Engine/Physics/CollisionShapes/CAABB.h"

template<typename T, std::uint8_t size, GLenum type, std::uint16_t position>
class CTemplateMeshBuffer : public CAbstractMeshBuffer
{
    std::uint8_t m_vertexAtribPointer;
protected:
    void CustomDestroy();

    void EnableAttribArray() override;
public:
    CTemplateMeshBuffer(CAbstractMesh* abstract_mesh, std::uint16_t index);
    void Initialize(const std::vector<T>& data);
};

template <typename T, std::uint8_t size, GLenum type, std::uint16_t position>
void CTemplateMeshBuffer<T, size, type, position>::CustomDestroy()
{
}

template <typename T, std::uint8_t size, GLenum type, std::uint16_t position>
void CTemplateMeshBuffer<T, size, type, position>::EnableAttribArray()
{
    glEnableVertexAttribArray(0);
}

template <typename T, std::uint8_t size, GLenum type, std::uint16_t position>
CTemplateMeshBuffer<T, size, type, position>::CTemplateMeshBuffer(CAbstractMesh* abstract_mesh, std::uint16_t index) : CAbstractMeshBuffer(abstract_mesh, index)
{
}

template <typename T, std::uint8_t size, GLenum type, std::uint16_t position>
void CTemplateMeshBuffer<T, size, type, position>::Initialize(const std::vector<T>& data)
{
    Init();
    Bind();
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof data[0], data.data(), GL_STATIC_DRAW);
    EnableAttribArray();
    glVertexAttribPointer(0, size, type, false, sizeof(T), 0);
}

template<std::uint16_t position>
using CVector3MeshBuffer = CTemplateMeshBuffer<EngineMath::SVector3f, 3, GL_FLOAT, position>;

#endif
