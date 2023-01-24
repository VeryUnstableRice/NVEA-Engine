#include "CSound.h"

#include <fstream>

#include "Engine/CEngine.h"

void CSound::FreeBuffers()
{
    if(!m_isInit) return;

    alDeleteBuffers(1, &m_buffer);
    m_isInit = false;
}

static bool is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } bint = { 0x01020304 };

    return bint.c[0] == 1;
}

std::vector<char> CSound::LoadWAV(const std::string& filePath, int& channel, int& sample_rate, int& beats_per_second)
{
    auto ToInt = [](char* buffer, int len)
    {
        int a = 0;
        if (is_big_endian())
            for (int i = 0; i<len; i++)
                ((char*)&a)[i] = buffer[i];
        else
            for (int i = 0; i<len; i++)
                ((char*)&a)[3 - i] = buffer[i];
        return a;
    };
    
    char buffer[4];
    std::ifstream in(filePath.c_str(), std::ios::binary);
    in.read(buffer, 4);
    if (strncmp(buffer, "RIFF", 4) != 0)
    {
        return std::vector<char>{};
    }

    in.ignore(20);
    channel = ToInt(buffer, 2);
    in.read(buffer, 4);
    sample_rate = ToInt(buffer, 4);
    in.ignore(6);
    in.read(buffer, 2);
    beats_per_second = ToInt(buffer, 2);
    in.ignore(4);
    in.read(buffer, 4);
    int size = ToInt(buffer, 4);
    
    std::vector<char> data{};
    data.resize(size);
    in.read(&data[0], size);
    return data;
}


void CSound::Init(const std::string& filePath)
{
    if(m_isInit) return;
    
    alGenBuffers(1, &m_buffer);
    std::vector<char> data = LoadWAV(filePath, m_channel, m_sample_rate, m_beats_per_second);

    const ALenum format_lookup[] = {
        AL_FORMAT_STEREO16, AL_FORMAT_STEREO8, AL_FORMAT_MONO16, AL_FORMAT_MONO8
    };

    alBufferData(m_buffer, format_lookup[(m_channel == 1) | ((m_beats_per_second == 8) << 1)], data.data(), data.size(), m_sample_rate);
    
    m_isInit = true;
}

void CSound::OnDestroy()
{
    CObject::OnDestroy();
    FreeBuffers();
}
