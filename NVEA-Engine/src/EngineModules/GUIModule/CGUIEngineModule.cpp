#include "CGUIEngineModule.h"

CGUIEngineModule* CGUIEngineModule::Instance = nullptr;

void CGUIEngineModule::AddCanvas(CGUICanvas* canvas)
{
    m_canvases.push_back(canvas);
}

void CGUIEngineModule::RemoveCanvas(CGUICanvas* canvas)
{
    std::erase(m_canvases, canvas);
}

void CGUIEngineModule::Tick(double DeltaTime)
{
    
}

bool CGUIEngineModule::Load()
{
    Instance = this;
    return true;
}

void CGUIEngineModule::Unload()
{
    Instance = nullptr;
}

std::string CGUIEngineModule::ModuleName()
{
    return "GUI Module";
}