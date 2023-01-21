#include "CEngineSoundModule.h"

#include <SDL2/SDL.h>


void CEngineSoundModule::Tick(double DeltaTime)
{
    
}
bool CEngineSoundModule::Load()
{
    SDL_Init(SDL_INIT_AUDIO);
    return true;
}

void CEngineSoundModule::Unload()
{
    
}

std::string CEngineSoundModule::ModuleName()
{
    return "Sound Module";
}
