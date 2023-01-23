#include "CEngineRenderModule.h"
#include "RenderPipeline/CRenderPipeline.h"
#include "Engine/CAbstractEngine.h"
#include "Engine/CEngine.h"

void CEngineRenderModule::Tick(double DeltaTime)
{
    m_renderPipeline->Render();
}

bool CEngineRenderModule::Load()
{
    m_renderPipeline = CreateObject<CRenderPipeline>();
    m_display.Init("noname", 640, 480);
    m_centerCursorEvent = CEngine::Engine->GetDynamicHash("center_cursor");
    return m_renderPipeline;
}

void CEngineRenderModule::Unload()
{
}

std::string CEngineRenderModule::ModuleName()
{
    return "Render Module";
}

bool CEngineRenderModule::Run()
{
    m_display.Run();
    return true;
}

void CEngineRenderModule::OnEvent(std::uint64_t eventID)
{
    if(m_centerCursorEvent == eventID)
        m_display.CenterCursor();
}

CRenderPipeline* CEngineRenderModule::GetRenderPipeline()
{
    return m_renderPipeline;
}
