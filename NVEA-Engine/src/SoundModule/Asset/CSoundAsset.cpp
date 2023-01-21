#include "CSoundAsset.h"

#include "Engine/CAbstractEngine.h"

void CSoundAsset::Initialiaze(const std::string& path)
{
    CSound* Sound = CreateObject<CSound>();
    Sound->Init(path);
    SetAsset(Sound);
}
