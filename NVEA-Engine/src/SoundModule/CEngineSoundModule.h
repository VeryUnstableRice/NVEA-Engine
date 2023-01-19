#ifndef CEngineSoundModule_Header
#define CEngineSoundModule_Header
#include "Engine/IEngineModuleInterface.h"

class CEngineSoundModule : public IEngineModuleInterface
{
public:
    virtual void Tick(double DeltaTime) = 0;
    virtual bool Load() = 0;
    virtual void Unload() = 0;
    std::string ModuleName() override;

    
};

#endif