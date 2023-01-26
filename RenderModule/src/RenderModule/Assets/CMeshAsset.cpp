#include "CMeshAsset.h"

#include "Engine/CAbstractEngine.h"
#include "RenderModule/Mesh/CStaticMesh.h"

bool CMeshAsset::NativeAsset(const std::string& path)
{
    if(path == "RenderPlane")
    {
        CStaticMesh* mesh = CreateObject<CStaticMesh>();
        mesh->Generate
        ({
            {0, 0, 0},
            {0, 1, 0},
            {1, 0, 0},

            {1, 0, 0},
            {0, 1, 0},
            {1, 1, 0},
        },
        {
            {0, 1},
            {0, 0},
            {1, 1},
            
            {1, 1},
            {0, 0},
            {1, 0},
        });
        SetAsset(mesh);
        return true;
    }
    return false;
}

void CMeshAsset::Initialiaze(const std::string& path)
{
    if(NativeAsset(path)) return;
}
