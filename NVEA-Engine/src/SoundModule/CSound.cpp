#include "CSound.h"

void CSound::FreeBuffers()
{
    if(!m_isInit) return;
    SDL_FreeWAV(m_wavBuffer);
    m_isInit = false;
}

void CSound::Init(const std::string& filePath)
{
    if(m_isInit) return;
    SDL_LoadWAV(filePath.c_str(), &m_wavSpec, &m_wavBuffer, &m_wavLength);
    m_isInit = true;
}

void CSound::OnDestroy()
{
    CObject::OnDestroy();
    FreeBuffers();
}
