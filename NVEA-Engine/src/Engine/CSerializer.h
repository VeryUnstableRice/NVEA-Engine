#pragma once
#include <string>

class CSerializer
{
    std::string m_path;
public:
    CSerializer() = delete;
    CSerializer(const std::string Path);
};
