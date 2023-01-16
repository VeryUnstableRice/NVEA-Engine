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
    double forward  = m_forward->CheckButtons(EButtonEvent::Down) -  m_backward->CheckButtons(EButtonEvent::Down);
    double right = m_right->CheckButtons(EButtonEvent::Down) -  m_left->CheckButtons(EButtonEvent::Down);

    if(!IsValid(m_playerPuppet)) return;
    CEntityTransformComponent* transform_component = m_playerPuppet->GetTransformComponent();
    SVector3f forward_vec = transform_component->GetForwardVector() * (float)forward;
    SVector3f right_vec = transform_component->GetRightVector() * (float)right;

    m_playerPuppet->GetTransformComponent()->Move((forward_vec+right_vec)*(float)DeltaTime*50.f);
    //m_playerPuppet->PrintLocation();
    //m_playerPuppet->Destroy();
}

void CDebugLevel::OnLevelChanged()
{
    GetLocalPlayer()->SetMouseFree(true);
    m_playerPuppet = SpawnEntity<CTestPlayerPuppet>();
    GetLocalPlayer()->SetPuppet(m_playerPuppet);

    m_forward   = CAbstractEngine::Engine->GetInputManager().GetInput("forward"     , true)->AddButton({SDL_SCANCODE_W});
    m_backward  = CAbstractEngine::Engine->GetInputManager().GetInput("backward"    , true)->AddButton({SDL_SCANCODE_S});
    m_left      = CAbstractEngine::Engine->GetInputManager().GetInput("left"        , true)->AddButton({SDL_SCANCODE_A});
    m_right     = CAbstractEngine::Engine->GetInputManager().GetInput("right"       , true)->AddButton({SDL_SCANCODE_D});


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