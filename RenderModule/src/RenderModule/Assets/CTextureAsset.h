#pragma once
#include "Engine/AssetManager/Asset/CAbstractAsset.h"
#include "RenderModule/RenderingObjects/CTexture.h"

class CTextureAsset : public CTemplateAsset<CTexture>
{
public:
    void Initialiaze(const std::string& path) override;
};
