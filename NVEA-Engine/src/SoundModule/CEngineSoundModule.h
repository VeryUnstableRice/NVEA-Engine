#ifndef CEngineSoundModule_Header
#define CEngineSoundModule_Header
#include "Engine/IEngineModuleInterface.h"
#include <alc.h>

//TODO: reimplement all of this with OpenAL, SDL is doing a decent job but openal is doing the best job

class CEngineSoundModule : public IEngineModuleInterface
{
    ALCdevice* m_device = nullptr;
    ALCcontext* m_context = nullptr;
public:
    void Tick(double DeltaTime) override;
    bool Load() override;
    void Unload() override;
    std::string ModuleName() override;
};

#endif