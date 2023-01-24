#ifndef CInputEngineModule_Header
#define CInputEngineModule_Header
#include "Engine/IEngineModuleInterface.h"
#include "InputManager/CInputManager.h"

class CInputEngineModule : public IEngineModuleInterface
{
    CObjectPtr<CInputManager> m_inputManager;
    std::uint64_t m_centerCursorEvent;
public:
    void Tick(double DeltaTime) override;
    bool Load() override;
    void Unload() override;
    std::string ModuleName() override;
    bool ForceExit() override;

    CInputManager& GetInputManager() const;
    static CInputEngineModule* Instance;
};

#endif