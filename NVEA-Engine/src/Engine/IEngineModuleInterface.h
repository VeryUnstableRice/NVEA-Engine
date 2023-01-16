#ifndef IEngineModuleInterface_Header
#define IEngineModuleInterface_Header

class IEngineModuleInterface
{
public:
    virtual ~IEngineModuleInterface() = default;
    virtual void Tick(double DeltaTime) = 0;
    virtual void Load() = 0;
    virtual void Unload() = 0;
};

#endif