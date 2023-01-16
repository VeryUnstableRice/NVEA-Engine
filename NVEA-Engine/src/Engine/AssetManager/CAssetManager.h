#ifndef CFILEMANAGER_HEADER
#define CFILEMANAGER_HEADER
#include <string>
#include <unordered_map>
#include <memory>

#include "Asset/CAbstractAsset.h"
#include "Engine/CAbstractEngine.h"


class CAssetManager : public CObject
{
	using Assets = std::unordered_map<std::string, CObjectPtr<CAbstractAsset>>;
	Assets m_assets;
public:
	void ClearAssets();
	CAbstractAsset* GetAsset(const std::string& Path);
	
	template<typename T = CAbstractAsset>
	T* CreateAsset(const std::string& Path)
	{
		Assets::iterator it = m_assets.find(Path);
		if(it != m_assets.end())
			return dynamic_cast<T*>(&*it->second.get());
		
		T* Asset = CreateObject<T>();
		Asset->Initialiaze(Path);
		m_assets.emplace(Path, Asset);
		return Asset;
	}
};

#endif
