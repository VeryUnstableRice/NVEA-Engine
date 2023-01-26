#include "CTextureAsset.h"

#include "Engine/CAbstractEngine.h"

void CTextureAsset::Initialiaze(const std::string& path)
{
    CTexture* texture = CreateObject<CTexture>();
    texture->Init(path);
    SetAsset(texture);
}
