#include "CEngine.h"

CEngine* CEngine::Engine = nullptr;

CEngine::CEngine()
{
    Engine = this;
}

CEngine::~CEngine()
{
}

void CEngine::LoadEngine()
{
    m_engineModules.push_back(m_renderModule = new CEngineRenderModule());
    CAbstractEngine::LoadEngine();
}

void CEngine::UnloadEngine()
{
    CAbstractEngine::UnloadEngine();
}

CEngineRenderModule* CEngine::GetRenderModule()
{
    return m_renderModule;
}
