#include "CDebugLevel.h"

#include <iostream>

#include "CTestGameInstance.h"
#include "Engine/InputManager/CBoundInput.h"
#include "Engine/Object/Puppet/CPlayer.h"
#include "Engine/RenderPipeline/CMeshRenderEntity.h"

void CDebugLevel::LevelTick(double DeltaTime)
{

}

void CDebugLevel::LevelPhysicsTick(double DeltaTime)
{
    //m_playerPuppet->PrintLocation();
    //m_playerPuppet->Destroy();
}

void CDebugLevel::OnLevelChanged()
{
    GetLocalPlayer()->SetMouseFree(true);
    m_playerPuppet = SpawnEntity<CTestPlayerPuppet>();
    GetLocalPlayer()->SetPuppet(m_playerPuppet);


    m_testMesh = CreateObject<CStaticMesh>();
    float size = 1.f;
    m_testMesh->Generate(
        {
            {size, size, size},
            {0, size, size},
            {0, 0, size},

            {0, 0, size},
            {size, 0, size},
            {size, size, size},

            //BACK
            {0, size, 0},
            {size, size, 0},
            {size, 0, 0},

            {size, 0, 0},
            {0, 0, 0},
            {0, size, 0},

            //RIGHT
            {size, size, 0},
            {size, size, size},
            {size, 0, size},

            {size, 0, size},
            {size, 0, 0},
            {size, size,  0},

            //LEFT
            {0, size, size},
            {0, size, 0},
            {0, 0, 0},

            {0, 0, 0},
            {0, 0, size},
            {0, size, size},

            //TOP
            {size, size, 0},
            {0, size, 0},
            {0, size, size},

            {0, size, size},
            {size, size, size},
            {size, size, 0},

            //BOTTOM
            {0, 0, 0},
            {size, 0, 0},
            {size, 0, size},

            {size, 0, size},
            {0, 0, size},
            {0, 0, 0}
        });
    m_renderTestMesh = SpawnEntity<CMeshRenderEntity>();
    m_renderTestMesh->SetMesh(m_testMesh);
    m_renderTestMesh->SetShader(CTestGameInstance::Instance->DefaultShader);
}

void CDebugLevel::OnUnloadedLevel()
{
    
}