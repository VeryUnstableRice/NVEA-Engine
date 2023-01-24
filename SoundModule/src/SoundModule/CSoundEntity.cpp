#include "CSoundEntity.h"

#include "CSound.h"

void CSoundEntity::SetSound(CSound* sound)
{
    if(m_sound == sound) return;
    if(m_sound) alDeleteSources(1, &m_source);
    m_sound = sound;
    if(!m_sound) return;
    alGenSources(1, &m_source);
    alSourcei(m_source, AL_BUFFER, m_sound->m_buffer);

    m_init = true;
}

void CSoundEntity::PlaySound()
{
    if(!m_init || !m_sound || IsPlaying()) return;
    alSourcePlay(m_source);
}

void CSoundEntity::OnDestroy()
{
    CEntity::OnDestroy();
    SetSound(nullptr);
}
