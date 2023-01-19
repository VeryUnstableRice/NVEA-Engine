#include "CEngineRenderModule.h"

#include "Engine/CAbstractEngine.h"
#include "Engine/RenderPipeline/CRenderPipeline.h"

void CEngineRenderModule::Tick(double DeltaTime)
{
    m_renderPipeline->Render();
}

bool CEngineRenderModule::Load()
{
    m_renderPipeline = CreateObject<CRenderPipeline>();
    return m_renderPipeline;
}

void CEngineRenderModule::Unload()
{
}

std::string CEngineRenderModule::ModuleName()
{
    return "Render Module";
}

CRenderPipeline* CEngineRenderModule::GetRenderPipeline()
{
    return m_renderPipeline;
}
