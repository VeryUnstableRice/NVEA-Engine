#include "CCameraBuffer.h"

#include <iostream>

#include "Engine/CAbstractEngine.h"
#include "Engine/Math/Math.h"
#include "RenderModule/Camera/CCameraEntity.h"
#include "RenderModule/Mesh/AbstractMesh/CAbstractMesh.h"
#include "RenderModule/RenderingObjects/CShader.h"
#include "RenderModule/RenderPipeline/CMeshRenderEntity.h"
#include "RenderModule/RenderingObjects/CRenderBuffer.h"
#include "Engine/CEngine.h"
#include "Engine/AssetManager/CAssetManager.h"
#include "RenderModule/Assets/CMeshAsset.h"
#include "RenderModule/Assets/CShaderAsset.h"
#include "RenderModule/Mesh/CStaticMesh.h"
#include "RenderModule/RenderingObjects/CTexture.h"

void CCameraBuffer::CheckForFBOErrors(std::string& output)
{
    GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE)
    {
        constexpr std::pair<GLuint, const char*> errors[] =
        {
            {GL_FRAMEBUFFER_UNDEFINED, "GL_FRAMEBUFFER_UNDEFINED"},
            {GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT , "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT "},
            {GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT , "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT "},
            {GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER , "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER "},
            {GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER , "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER "},
            {GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE , "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE  "},
            {GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS  , "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS  "},
        };

        for(const std::pair<GLuint, std::string>& possible_error : errors)
        {
            if(status != possible_error.first) continue;
            output = possible_error.second;
        }
    }
}

void CCameraBuffer::InitializeComponent()
{
    CEntityComponent::InitializeComponent();
    m_texture = CreateObject<CTexture>();
    m_depthBuffer = CreateObject<CRenderBuffer>();
    
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    m_texture->AttachToBuffer(this, GL_COLOR_ATTACHMENT0);
    m_depthBuffer->AttachToBuffer(this, GL_DEPTH24_STENCIL8, GL_DEPTH_ATTACHMENT);

    std::string output;
    CheckForFBOErrors(output);
    CEngine::Engine->PrintLog(!output.empty() ? "Framebuffer is incomplete: " + output: "Framebuffer has been initialized successfully!", GL_LOG);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CCameraBuffer::DeinitializeComponent()
{
    CEntityComponent::DeinitializeComponent();
}

void CCameraBuffer::PrepareForRender()
{
    std::erase(m_renderEntites, nullptr);
    std::sort(m_renderEntites.begin(), m_renderEntites.end(), [](const CWeakObjectPtr<class CMeshRenderEntity>& A, const CWeakObjectPtr<class CMeshRenderEntity>& B)
    {
        return
                A->GetRenderPriority() > B->GetRenderPriority() &&
                A->GetShader() > B->GetShader() &&
                A->GetTexture() > B->GetTexture();
    });
}

void CCameraBuffer::SetSizes(std::uint32_t width, std::uint32_t height)
{
    if(m_width == width && m_height == height) return;
    m_width = width;
    m_height = height;

    m_texture->ReallocateSize(this);
    m_depthBuffer->ReallocateSize(this, GL_DEPTH24_STENCIL8);
}

void CCameraBuffer::ResetRenderEntities()
{
    m_renderEntites.clear();
}

void CCameraBuffer::RenderObjects()
{
    CCameraEntity* Camera = dynamic_cast<CCameraEntity*>(GetOwner());
    if(!Camera) return;
    
    EngineMath::SMatrix4f Projection = Camera->getProjection();
    EngineMath::SMatrix4f ViewMatrix = Camera->GetView(true);

    
    CShader*    Shader  = nullptr;
    CTexture*   Texture = nullptr;
    EngineMath::SVector4f   Color;
    EngineMath::SMatrix4f   ModelMatrix;
    bool        IsWireframe = false;

    int CurrentIteration = 0;
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(CMeshRenderEntity* render_entity : m_renderEntites)
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
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CCameraBuffer::RenderToScreen()
{
    if(!m_screen) m_screen = reinterpret_cast<CStaticMesh*>(CEngine::Engine->GetAssetManager().CreateAsset<CMeshAsset>("RenderPlane")->GetAsset());
    if(!m_shader) m_shader = CEngine::Engine->GetAssetManager().CreateAsset<CShaderAsset>("./res/DefaultShader/DefaultPostProcess")->GetAsset();
    m_shader->Use();
    m_shader->SetUniform(glm::ortho(0.f, 1.f, 1.f, 0.f), "viewmatrix");
    m_texture->Bind();
    m_screen->Render(GL_TRIANGLES);
}
