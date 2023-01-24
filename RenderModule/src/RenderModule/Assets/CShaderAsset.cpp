#include "CShaderAsset.h"

#include "Engine/CAbstractEngine.h"

void CShaderAsset::Initialiaze(const std::string& path)
{
    CShader* Shader = CreateObject<CShader>();
    Shader->Init(path, 1);
    SetAsset(Shader);
}
