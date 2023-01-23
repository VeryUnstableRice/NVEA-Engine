#include "CInputEngineModule.h"

#include "Engine/CAbstractEngine.h"
#include "Engine/CEngine.h"

CInputEngineModule* CInputEngineModule::Instance =  nullptr;

void CInputEngineModule::Tick(double DeltaTime)
{
    
}

bool CInputEngineModule::Load()
{
    Instance = this;
    m_inputManager = CreateObject<CInputManager>();
    m_centerCursorEvent = CEngine::Engine->GetDynamicHash("center_cursor");
    return true;
}

void CInputEngineModule::Unload()
{
    Instance = nullptr;
}

std::string CInputEngineModule::ModuleName()
{
    return "Input Module";
}

bool CInputEngineModule::ForceExit()
{
    return m_inputManager->Update();
}

CInputManager& CInputEngineModule::GetInputManager() const
{
    return *m_inputManager;
}
