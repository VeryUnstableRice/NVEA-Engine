#ifndef GUIEngineModule_Header
#define GUIEngineModule_Header
#include <vector>

#include "CGUICanvas.h"
#include "Engine/IEngineModuleInterface.h"
#include "Engine/MemoryManager/CObjectPtr.h"

class CGUIEngineModule : public IEngineModuleInterface
{
    std::vector<CObjectPtr<CGUICanvas>> m_canvases;

    void AddCanvas(CGUICanvas* canvas);
    void RemoveCanvas(CGUICanvas* canvas);
    friend class CGUICanvas;
public:
    void Tick(double DeltaTime) override;
    bool Load()                 override;
    void Unload()               override;
    std::string ModuleName()    override;

    static CGUIEngineModule* Instance;
};

#endif