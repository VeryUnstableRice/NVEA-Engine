#pragma once
#include "Engine/Object/Puppet/CPuppetEntity.h"

class CTestPlayerPuppet : public CPuppetEntity
{
    void ManageInput(CInputManager* input_manager) override;

    CObjectPtr<class CCameraEntity> m_cameraEntity;

    double m_yaw;
    
    void ManageCamera(double DeltaTime);
public:
    void OnConstruct() override;
    void Tick(double DeltaTime) override;
    void PhysicsTick(double PhysicsDeltaTime) override;
};
