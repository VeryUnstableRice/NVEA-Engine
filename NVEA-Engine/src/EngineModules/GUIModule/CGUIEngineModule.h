#ifndef GUIEngineModule_Header
#define GUIEngineModule_Header
#include <vector>

#include "CGUICanvas.h"
#include "Engine/IEngineModuleInterface.h"
#include "Engine/MemoryManager/CObjectPtr.h"

class CGUIEngineModule : public IEngineModuleInterface
{
    std::vector<CObjectPtr<CGUICanvas>> m_canvasArray;   
public:
    void Tick(double DeltaTime) override;
    bool Load()                 override;
    void Unload()               override;
    std::string ModuleName()    override;

    void OnObjectCreated(class CObject* object) override;
    void OnObjectDestroyed(class CObject* object) override;
};

#endif