#include "CEngineSoundModule.h"

#include "Engine/CEngine.h"


void CEngineSoundModule::Tick(double DeltaTime)
{
    
}
bool CEngineSoundModule::Load()
{
    m_device = alcOpenDevice(nullptr);
    if (!m_device)
    {
        CEngine::Engine->PrintLog("Error: Failed to open the default audio device", ENGINE_LOADING);
        return false;
    }
    m_context = alcCreateContext(m_device, nullptr);
    if(!m_context)
    {
        CEngine::Engine->PrintLog("Error: Failed to create a new audio context", ENGINE_LOADING);
        return false;
    }
    alcMakeContextCurrent(m_context);
    
    return true;
}

void CEngineSoundModule::Unload()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}

std::string CEngineSoundModule::ModuleName()
{
    return "Sound Module";
}
