#ifndef CSound_Header
#define CSound_Header
#include "Engine/Object/CObject.h"
#include <SDL2/SDL_audio.h>
#include <al.h>
#include <alc.h>
#include <vector>

class CSound : public CObject
{
    bool m_isInit = false;
    ALuint m_buffer;
    int m_channel;
    ALsizei m_sample_rate;
    int m_beats_per_second;
    
    void FreeBuffers();

    friend class CSoundEntity;

    std::vector<char> LoadWAV(const std::string& filePath, int& channel, int& sample_rate, int& beats_per_second);
public:
    void Init(const std::string& filePath);

    void OnDestroy() override;
};

#endif