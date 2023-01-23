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

    virtual bool Run() { return false; };
    virtual bool ForceExit() { return false; }
    virtual void OnEvent(std::uint64_t eventID) {}
    virtual void OnObjectCreated(class CObject* object) {}
    virtual void OnObjectDestroyed(class CObject* object) {}
};

#endif