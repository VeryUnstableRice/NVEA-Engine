#include "CSound.h"

#include <fstream>

#include "Engine/CEngine.h"

void CSound::FreeBuffers()
{
    if(!m_isInit) return;

    alDeleteBuffers(1, &m_buffer);
    m_isInit = false;
}

bool isBigEndian()
{
    int a = 1;
    return !((char*)&a)[0];
}

int convertToInt(char* buffer, int len)
{
    int a = 0;
    if (!isBigEndian())
        for (int i = 0; i<len; i++)
            ((char*)&a)[i] = buffer[i];
    else
        for (int i = 0; i<len; i++)
            ((char*)&a)[3 - i] = buffer[i];
    return a;
}

std::vector<char> loadWAV(const std::string& filePath, int& channel, int& samplerate, int& bps)
{
    char buffer[4];
    std::ifstream in(filePath.c_str(), std::ios::binary);
    in.read(buffer, 4);
    if (strncmp(buffer, "RIFF", 4) != 0)
    {
        return std::vector<char>{};;
    }
    in.read(buffer, 4);
    in.read(buffer, 4);      //WAVE
    in.read(buffer, 4);      //fmt
    in.read(buffer, 4);      //16
    in.read(buffer, 2);      //1
    in.read(buffer, 2);
    channel = convertToInt(buffer, 2);
    in.read(buffer, 4);
    samplerate = convertToInt(buffer, 4);
    in.read(buffer, 4);
    in.read(buffer, 2);
    in.read(buffer, 2);
    bps = convertToInt(buffer, 2);
    in.read(buffer, 4);      //data
    in.read(buffer, 4);
    int size = convertToInt(buffer, 4);
    std::vector<char> data{};
    data.resize(size);
    in.read(&data[0], size);
    return data;
}

std::vector<char> CSound::LoadWAV(const std::string& filePath, int& channel, int& sample_rate, int& beats_per_second)
{
    return loadWAV(filePath, channel, sample_rate, beats_per_second);
}


void CSound::Init(const std::string& filePath)
{
    if(m_isInit) return;
    
    alGenBuffers(1, &m_buffer);
    std::vector<char> data = loadWAV(filePath, m_channel, m_sample_rate, m_beats_per_second);

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
