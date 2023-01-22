#include "CGUIEngineModule.h"

void CGUIEngineModule::Tick(double DeltaTime)
{
    
}

bool CGUIEngineModule::Load()
{
    return true;
}

void CGUIEngineModule::Unload()
{
    
}

std::string CGUIEngineModule::ModuleName()
{
    return "GUI Module";
}

void CGUIEngineModule::OnObjectCreated(CObject* object)
{
    IEngineModuleInterface::OnObjectCreated(object);
    if(CGUICanvas* canvas = dynamic_cast<CGUICanvas*>(object))
        m_canvasArray.push_back(canvas);
}

void CGUIEngineModule::OnObjectDestroyed(CObject* object)
{
    IEngineModuleInterface::OnObjectDestroyed(object);
    if(CGUICanvas* canvas = dynamic_cast<CGUICanvas*>(object))
        std::erase(m_canvasArray, canvas);
}
