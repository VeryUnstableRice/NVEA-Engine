#ifndef CSoundEntity_Header
#define CSoundEntity_Header
#include "Engine/Object/Entity/CEntity.h"


class CSoundEntity : public CEntity
{
    class CSound* m_sound;
    SDL_AudioDeviceID m_deviceID;
public:
    void SetSound(CSound* sound);
    void PlaySound();
    bool IsPlaying() const;
};

inline bool CSoundEntity::IsPlaying() const
{
    return m_sound && SDL_GetQueuedAudioSize(m_deviceID) >= 1 && SDL_GetAudioDeviceStatus(m_deviceID) == SDL_AUDIO_PLAYING;
}

#endif