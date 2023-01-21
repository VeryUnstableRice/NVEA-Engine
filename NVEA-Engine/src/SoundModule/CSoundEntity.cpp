#include "CSoundEntity.h"

#include "CSound.h"

void CSoundEntity::SetSound(CSound* sound)
{
    if(m_sound)
        SDL_CloseAudioDevice(m_deviceID);
    if(m_sound = sound)
        m_deviceID = SDL_OpenAudioDevice(nullptr, 0, &sound->m_wavSpec, nullptr, 0);
}

void CSoundEntity::PlaySound()
{
    if(!m_sound || IsPlaying()) return;

    SDL_QueueAudio(m_deviceID, m_sound->m_wavBuffer, m_sound->m_wavLength);
    SDL_PauseAudioDevice(m_deviceID, 0);
}
