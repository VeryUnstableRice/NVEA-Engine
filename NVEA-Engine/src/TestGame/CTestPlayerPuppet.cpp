#include "CTestPlayerPuppet.h"

#include "CTestGameInstance.h"
#include "Engine/CEngine.h"
#include "Engine/Camera/CCameraEntity.h"
#include "Engine/CLevel.h"
#include "Engine/Camera/CCameraManager.h"

void CTestPlayerPuppet::ManageInput(CInputManager* input_manager)
{
}

void CTestPlayerPuppet::ManageCamera(double DeltaTime)
{
    CInputManager& manager = CEngine::Engine->GetInputManager();//.CenterMouse();
    GetPlayer()->SetMouseFree(false);
    glm::vec2 mousepos = manager.GetMouseRelative();

    STransform cameraTransform = m_cameraEntity->GetTransformComponent()->GetLocalTransform();
    //m_yaw += mousepos.y;
    cameraTransform.Rotation.Yaw    += (double)mousepos.x*-DeltaTime*100.0;
    cameraTransform.Rotation.Pitch  += (double)mousepos.y*-DeltaTime*100.0;
    m_cameraEntity->GetTransformComponent()->SetLocalTransform(cameraTransform);

    CEngine::Engine->PrintLog(std::to_string(cameraTransform.Rotation.Yaw) + " " + std::to_string(cameraTransform.Rotation.Pitch), NORMAL);
}

void CTestPlayerPuppet::OnConstruct()
{
    CPuppetEntity::OnConstruct();
    m_cameraEntity = GetLevel()->SpawnEntity<CCameraEntity>();
    m_cameraEntity->AttachTo(this);
    m_cameraEntity->MakePerspective(90.f, 9.f/16.f, 0.1f, 1000.f);
    CAbstractEngine::Engine->GetGameInstance()->GetCameraManager()->SetCurrentCamera(m_cameraEntity);
    m_yaw = 0;
}

void CTestPlayerPuppet::Tick(double DeltaTime)
{
    CPuppetEntity::Tick(DeltaTime);
}

void CTestPlayerPuppet::PhysicsTick(double PhysicsDeltaTime)
{
    CPuppetEntity::PhysicsTick(PhysicsDeltaTime);
    ManageCamera(PhysicsDeltaTime);
}
