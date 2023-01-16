#include "CAssetManager.h"

#include <ranges>


void CAssetManager::ClearAssets()
{
    m_assets.clear();
}

CAbstractAsset* CAssetManager::GetAsset(const std::string& Path)
{
    Assets::iterator it = m_assets.find(Path);
    if(it == m_assets.end()) return nullptr;
    return it->second.get();
}
