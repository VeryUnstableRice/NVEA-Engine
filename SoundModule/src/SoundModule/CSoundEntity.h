#ifndef CSoundEntity_Header
#define CSoundEntity_Header
#include <al.h>

#include "Engine/Object/Entity/CEntity.h"


class CSoundEntity : public CEntity
{
    class CSound* m_sound;
    ALuint m_source;
    bool m_init = false;
public:
    void SetSound(CSound* sound);
    void PlaySound();
    bool IsPlaying() const;

    void OnDestroy() override;
};

inline bool CSoundEntity::IsPlaying() const
{
    if(!m_sound) return false;
    ALint state;
    alGetSourcei(m_source, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

#endif