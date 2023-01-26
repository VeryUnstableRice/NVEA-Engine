#include "CEngineRenderModule.h"
#include "RenderPipeline/CRenderPipeline.h"
#include "RenderModule/Camera/CCameraManager.h"
#include "Engine/CAbstractEngine.h"
#include "Engine/CEngine.h"

CEngineRenderModule* CEngineRenderModule::Instance = nullptr;

void CEngineRenderModule::Tick(double DeltaTime)
{
}

bool CEngineRenderModule::Load()
{
    m_renderPipeline = CreateObject<CRenderPipeline>();
    m_display.Init("noname", 640, 480);
    m_centerCursorEvent = CEngine::Engine->GetDynamicHash("center_cursor");
    m_cameraManager = CreateObject<CCameraManager>();
    Instance = this;
    return m_renderPipeline;
}

void CEngineRenderModule::Unload()
{
    Instance = nullptr;
}

std::string CEngineRenderModule::ModuleName()
{
    return "Render Module";
}

bool CEngineRenderModule::Run()
{
    m_display.Run();
    m_renderPipeline->Render();
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
