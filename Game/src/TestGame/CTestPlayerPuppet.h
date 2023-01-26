#pragma once
#include "Engine/Object/Entity/Puppet/CPuppetEntity.h"

class CTestPlayerPuppet : public CPuppetEntity
{
    CObjectPtr<class CCameraEntity> m_cameraEntity;

    float m_yaw, m_pitch;
    CObjectPtr<class CBoundInput> m_forward;
    CObjectPtr<class CBoundInput> m_backward;
    CObjectPtr<class CBoundInput> m_left;
    CObjectPtr<class CBoundInput> m_right;
    void ManageCamera(double DeltaTime);
public:
    void OnConstruct() override;
    void Tick(double DeltaTime) override;
    void PhysicsTick(double PhysicsDeltaTime) override;
};
