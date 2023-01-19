#ifndef IEngineModuleInterface_Header
#define IEngineModuleInterface_Header
#include <string>

class IEngineModuleInterface
{
public:
    virtual ~IEngineModuleInterface() = default;
    virtual void Tick(double DeltaTime) = 0;
    virtual bool Load() = 0;
    virtual void Unload() = 0;
    virtual std::string ModuleName() = 0;
};

#endif