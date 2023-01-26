#ifndef CCameraBuffer_Header
#define CCameraBuffer_Header
#include <vector>
#include <glad/glad.h>
#include "Engine/MemoryManager/CObjectPtr.h"
#include "Engine/Object/Entity/EntityComponents/CEntityComponent.h"

class CCameraBuffer : public CEntityComponent
{
    CObjectPtr<class CTexture> m_texture = nullptr;
    CObjectPtr<class CRenderBuffer> m_depthBuffer = nullptr;

    std::vector<CWeakObjectPtr<class CMeshRenderEntity>> m_renderEntites;

    GLuint m_fbo;

    std::uint32_t m_width = 640;
    std::uint32_t m_height = 480;

    void PrepareForRender();

    friend class CTexture;
    friend class CRenderBuffer;

    CObjectPtr<class CStaticMesh> m_screen = nullptr;
    CObjectPtr<class CShader> m_shader = nullptr;
protected:
    void CheckForFBOErrors(std::string& output);
    void InitializeComponent() override;
    void DeinitializeComponent() override;
public:
    void SetSizes(std::uint32_t width, std::uint32_t height);
    void AddRenderEntity(class CMeshRenderEntity* render_entity);
    void RemoveRenderEntity(class CMeshRenderEntity* render_entity);
    void ResetRenderEntities();
    
    void RenderObjects();
    CTexture* GetTexture();

    void RenderToScreen();
};

inline void CCameraBuffer::AddRenderEntity(CMeshRenderEntity* render_entity)
{
    m_renderEntites.push_back(render_entity);
}

inline void CCameraBuffer::RemoveRenderEntity(CMeshRenderEntity* render_entity)
{
    std::erase(m_renderEntites, render_entity);
}

inline CTexture* CCameraBuffer::GetTexture()
{
    return m_texture;
}

#endif