#pragma once
#include "Engine/AssetManager/Asset/CAbstractAsset.h"
#include "RenderModule/Mesh/AbstractMesh/CAbstractMesh.h"

class CMeshAsset  : public CTemplateAsset<CAbstractMesh>
{
    bool NativeAsset(const std::string& path);
public:
    void Initialiaze(const std::string& path) override;
};
