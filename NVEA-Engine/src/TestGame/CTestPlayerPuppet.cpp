#include "CTestPlayerPuppet.h"

#include "CTestGameInstance.h"
#include "Engine/CEngine.h"
#include "Engine/Camera/CCameraEntity.h"
#include "Engine/CLevel.h"
#include "Engine/Camera/CCameraManager.h"
#include "Engine/InputManager/CBoundInput.h"

void CTestPlayerPuppet::ManageInput(CInputManager* input_manager)
{
    
}

void CTestPlayerPuppet::ManageCamera(double DeltaTime)
{
    CInputManager& manager = CEngine::Engine->GetInputManager();//.CenterMouse();
    GetPlayer()->SetMouseFree(false);
    glm::vec2 mousepos = manager.GetMouseRelative();

    //m_yaw += mousepos.y;
    m_pitch +=    mousepos.x*+DeltaTime*100.0;
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
    m_cameraEntity->MakePerspective(90.f, 9.f/16.f, 0.1f, 1000.f);
    CAbstractEngine::Engine->GetGameInstance()->GetCameraManager()->SetCurrentCamera(m_cameraEntity);
    m_yaw = 0;

    m_forward   = CAbstractEngine::Engine->GetInputManager().GetInput("forward"     , true)->AddButton({SDL_SCANCODE_W});
    m_backward  = CAbstractEngine::Engine->GetInputManager().GetInput("backward"    , true)->AddButton({SDL_SCANCODE_S});
    m_left      = CAbstractEngine::Engine->GetInputManager().GetInput("left"        , true)->AddButton({SDL_SCANCODE_A});
    m_right     = CAbstractEngine::Engine->GetInputManager().GetInput("right"       , true)->AddButton({SDL_SCANCODE_D});
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
    SVector3f forward_vec = transform_component->GetForwardVector() * (float)forward;
    SVector3f right_vec = transform_component->GetRightVector() * (float)right;

    GetTransformComponent()->Move((forward_vec+right_vec)*(float)PhysicsDeltaTime*25.f);
}
