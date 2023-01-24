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

CRenderPipeline::CRenderPipeline() : CObject()
{
}

void CRenderPipeline::Render()
{
    CCameraEntity* Camera = CEngineRenderModule::Instance->GetCameraManager().GetCurrentCamera();
    if(!Camera) return;
    
    EngineMath::SMatrix4f Projection = Camera->getProjection();
    EngineMath::SMatrix4f ViewMatrix = Camera->GetView(true);

    
    CShader*    Shader  = nullptr;
    CTexture*   Texture = nullptr;
    EngineMath::SVector4f   Color;
    EngineMath::SMatrix4f   ModelMatrix;
    bool        IsWireframe = false;

    int CurrentIteration = 0;
    glDisable(GL_CULL_FACE);
    for(CWeakObjectPtr<class CMeshRenderEntity>& render_entity : m_entities)
    {
        CAbstractMesh*  CurrentMesh         = render_entity->GetMesh();
        CShader*        CurrentShader       = render_entity->GetShader();
        CTexture*       CurrentTexture      = render_entity->GetTexture();
        EngineMath::SVector4f       CurrentColor        = render_entity->GetColor();
        EngineMath::SMatrix4f       CurrentModelMatrix  = render_entity->GetTransformComponent()->GetTransformMatrix(Camera->GetTransformComponent()->GetWorldTransform().Translation);
        bool            CurrentWireframe    = render_entity->GetWireframe();

        if(!CurrentMesh || !CurrentShader) continue;
        
        bool ShaderChanged = false;
        if(CurrentShader != Shader || CurrentIteration == 0)
        {
            Shader = CurrentShader;
            Shader->Use();
            Shader->SetUniform(Projection, "ProjectionMatrix");
            Shader->SetUniform(ViewMatrix, "ViewMatrix");
            ShaderChanged = true;
        }

        if(CurrentModelMatrix != ModelMatrix)
        {
            ModelMatrix = CurrentModelMatrix;
            Shader->SetUniform(ModelMatrix, "ModelMatrix");
        }
        
        if(CurrentTexture != Texture || ShaderChanged)
        {
            Texture = CurrentTexture;
            if(Texture) Texture->Bind();
            Shader->SetUniform(Texture != nullptr, "doesHaveTexture");
        }
        if(CurrentColor != Color || ShaderChanged)
        {
            Color = CurrentColor;
            Shader->SetUniform(Color, "color");
        }

        if(IsWireframe != CurrentWireframe || ShaderChanged)
        {
            IsWireframe = CurrentWireframe;
            if(IsWireframe)
            {
                glPolygonMode(GL_FRONT, GL_LINE);
                glPolygonMode(GL_BACK, GL_LINE);
                glDisable(GL_CULL_FACE);
            }
            else
            {
                glPolygonMode(GL_FRONT, GL_FILL);
                glPolygonMode(GL_BACK, GL_FILL);
                glEnable(GL_CULL_FACE);
            }
        }

        render_entity->GetMesh()->Render(GL_TRIANGLES);
        ++CurrentIteration;
    }
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
    PrepareForRender();
}

void CRenderPipeline::Unsubscribe(CMeshRenderEntity* Entity)
{
    std::erase(m_entities, Entity);
    PrepareForRender();
}
