#include "CRenderPipeline.h"

#include <map>

#include "CMeshRenderEntity.h"
#include "Engine/CAbstractGame.h"
#include "RenderModule/Camera/CCameraEntity.h"
#include "RenderModule/Camera/CCameraManager.h"
#include "RenderModule/Mesh/AbstractMesh/CAbstractMesh.h"
#include "RenderModule/RenderingObjects/CShader.h"
#include "RenderModule/RenderingObjects/CTexture.h"
#include "RenderModule/CEngineRenderModule.h"
#include "RenderModule/Camera/CCameraBuffer.h"

CRenderPipeline::CRenderPipeline() : CObject()
{
}

void CRenderPipeline::Render()
{
    CCameraEntity* Camera = CEngineRenderModule::Instance->GetCameraManager().GetCurrentCamera();
    if(!Camera) return;
    
    CCameraBuffer* buffer = Camera->GetCameraBuffer();
    buffer->ResetRenderEntities();
    for(int i = 0; i < m_entities.size(); ++i)
        buffer->AddRenderEntity(m_entities[i]);
    
    buffer->SetSizes(640, 480);
    buffer->RenderObjects();
    buffer->RenderToScreen();
}

auto operator>(const EngineMath::SVector4f& A, const EngineMath::SVector4f& B)
{
    return A.x > B.x && A.y > B.y && A.z > B.z;
}

void CRenderPipeline::PrepareForRender()
{
    std::sort(m_entities.begin(), m_entities.end(), [](const CWeakObjectPtr<class CMeshRenderEntity>& A, const CWeakObjectPtr<class CMeshRenderEntity>& B)
        {
            return
                A->GetRenderPriority() > B->GetRenderPriority() &&
                A->GetShader() > B->GetShader() &&
                A->GetTexture() > B->GetTexture() &&
                A->GetColor() > B->GetColor();
        });
}

void CRenderPipeline::Subscribe(CMeshRenderEntity* Entity)
{
    m_entities.push_back(Entity);
}

void CRenderPipeline::Unsubscribe(CMeshRenderEntity* Entity)
{
    std::erase(m_entities, Entity);
}
