#ifndef CShaderAsset_Header
#define CShaderAsset_Header
#include "CAbstractAsset.h"
#include "Engine/RenderingObjects/CShader.h"

class CShaderAsset : public CTemplateAsset<CShader>
{
public:
    void Initialiaze(const std::string& path) override;
};

#endif