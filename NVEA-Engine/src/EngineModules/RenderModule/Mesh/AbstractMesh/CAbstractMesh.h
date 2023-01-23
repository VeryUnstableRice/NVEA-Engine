#pragma once
#include <memory>
#include <vector>

#include <glad/glad.h>
#include "Engine/Object/CObject.h"
#include "MeshBuffer/CAbstractMeshBuffer.h"

class CAbstractMesh : public CObject
{
    bool m_isInit = false;
    std::vector<std::shared_ptr<CAbstractMeshBuffer>> m_meshBuffers;
    GLuint m_VAO;
    GLenum m_type;
protected:
    GLsizei m_indices;
    template<typename T>
    T* MakeBuffer()
    {
        std::shared_ptr<T> pointer = std::shared_ptr<T>(new T(this, m_meshBuffers.size()));
        m_meshBuffers.push_back(pointer);
        return pointer.get();
    }
    
    virtual void GenerateBuffers();
    void Init();
public:
    CAbstractMesh();
    virtual ~CAbstractMesh();
    
    void Clear();
    void BingVAO();
    void Render(GLenum type);
    inline bool IsInitialized() const { return m_isInit; }
};
