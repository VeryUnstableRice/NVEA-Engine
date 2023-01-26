#include "CTestPlayerPuppet.h"

#include "CTestGameInstance.h"
#include "Engine/CEngine.h"
#include "Engine/CLevel.h"
#include "RenderModule/Camera/CCameraEntity.h"
#include "RenderModule/Camera/CCameraManager.h"
#include "InputManager/CInputManager.h"
#include "InputManager/CBoundInput.h"
#include "CInputEngineModule.h"
#include <RenderModule/CEngineRenderModule.h>

#include "../../../NVEA-Engine/glad/glad.h"


void CTestPlayerPuppet::ManageCamera(double DeltaTime)
{
    CInputManager& manager = CInputEngineModule::Instance->GetInputManager();//.CenterMouse();
    GetPlayer()->SetMouseFree(false);
    EngineMath::SVector2f mousepos = manager.GetMouseRelative();

    m_pitch +=  mousepos.x*+DeltaTime*100.0;
    m_yaw   +=  mousepos.y*+DeltaTime*100.0;

    SEulerRotator player_rot;
    STransform Transform = GetTransformComponent()->GetLocalTransform();
    player_rot.Pitch = m_pitch;
    Transform.Rotation = ToQuaternions(player_rot);
    GetTransformComponent()->SetLocalTransform(Transform);
    
    STransform cameraTransform = m_cameraEntity->GetTransformComponent()->GetLocalTransform();
    SEulerRotator rotator;
    rotator.Yaw = m_yaw;
    cameraTransform.Rotation = ToQuaternions(rotator);
    m_cameraEntity->GetTransformComponent()->SetLocalTransform(cameraTransform);
}

void CTestPlayerPuppet::OnConstruct()
{
    CPuppetEntity::OnConstruct();
    m_cameraEntity = GetLevel()->SpawnEntity<CCameraEntity>();
    m_cameraEntity->AttachTo(this);
    //m_cameraEntity->MakePerspective(90.f, 1.f, 0.1f, 1000.f);


    CEngineRenderModule::Instance->GetCameraManager().SetCurrentCamera(m_cameraEntity);
    m_yaw = 0;

    CInputManager& manager = CInputEngineModule::Instance->GetInputManager();
    m_forward   = manager.GetInput("forward"     , true)->AddButton({SDL_SCANCODE_W});
    m_backward  = manager.GetInput("backward"    , true)->AddButton({SDL_SCANCODE_S});
    m_left      = manager.GetInput("left"        , true)->AddButton({SDL_SCANCODE_A});
    m_right     = manager.GetInput("right"       , true)->AddButton({SDL_SCANCODE_D});
}

void CTestPlayerPuppet::Tick(double DeltaTime)
{
    CPuppetEntity::Tick(DeltaTime);
}

void CTestPlayerPuppet::PhysicsTick(double PhysicsDeltaTime)
{
    CPuppetEntity::PhysicsTick(PhysicsDeltaTime);
    ManageCamera(PhysicsDeltaTime);

    double forward  = m_forward->CheckButtons(EButtonEvent::Down) -  m_backward->CheckButtons(EButtonEvent::Down);
    double right = m_right->CheckButtons(EButtonEvent::Down) -  m_left->CheckButtons(EButtonEvent::Down);

    CEntityTransformComponent* transform_component = GetTransformComponent();
    EngineMath::SVector3f forward_vec   = transform_component->GetForwardVector() * (float)forward;
    EngineMath::SVector3f right_vec     = transform_component->GetRightVector() * (float)right;

    STransform Transform = GetTransformComponent()->GetLocalTransform();
    //CEngine::Engine->PrintLog(std::to_string(ToEuler(Transform.Rotation).Pitch), NORMAL);

    GetTransformComponent()->Move((forward_vec+right_vec)*(float)PhysicsDeltaTime*25.f);
}
