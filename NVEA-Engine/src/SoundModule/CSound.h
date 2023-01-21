#ifndef CSound_Header
#define CSound_Header
#include <SDL2/SDL_audio.h>

#include "Engine/Object/CObject.h"

class CSound : public CObject
{
    SDL_AudioSpec m_wavSpec;
    Uint32 m_wavLength;
    Uint8* m_wavBuffer;

    bool m_isInit = false;

    void FreeBuffers();

    friend class CSoundEntity;
public:
    void Init(const std::string& filePath);

    void OnDestroy() override;
};

#endif