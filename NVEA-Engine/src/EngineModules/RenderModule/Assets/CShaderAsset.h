#ifndef CShaderAsset_Header
#define CShaderAsset_Header
#include "Engine/AssetManager/Asset/CAbstractAsset.h"
#include "EngineModules/RenderModule/RenderingObjects/CShader.h"

class CShaderAsset : public CTemplateAsset<CShader>
{
public:
    void Initialiaze(const std::string& path) override;
};

#endif