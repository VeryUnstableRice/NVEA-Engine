#include "CEngineRenderModule.h"

#include "Engine/CAbstractEngine.h"
#include "Engine/RenderPipeline/CRenderPipeline.h"

void CEngineRenderModule::Tick(double DeltaTime)
{
    m_renderPipeline->Render();
}

void CEngineRenderModule::Load()
{
    m_renderPipeline = CreateObject<CRenderPipeline>();
}

void CEngineRenderModule::Unload()
{
}

CRenderPipeline* CEngineRenderModule::GetRenderPipeline()
{
    return m_renderPipeline;
}
