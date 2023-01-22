#ifndef CSoundAsset_Header
#define CSoundAsset_Header
#include "Engine/AssetManager/Asset/CAbstractAsset.h"
#include "EngineModules/SoundModule/CSound.h"

class CSoundAsset : public CTemplateAsset<CSound>
{
public:
    void Initialiaze(const std::string& path) override;
};

#endif