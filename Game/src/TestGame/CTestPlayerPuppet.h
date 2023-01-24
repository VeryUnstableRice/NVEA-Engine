#pragma once
#include "Engine/Object/Puppet/CPuppetEntity.h"

class CTestPlayerPuppet : public CPuppetEntity
{
    CObjectPtr<class CCameraEntity> m_cameraEntity;

    float m_yaw, m_pitch;
    CWeakObjectPtr<class CBoundInput> m_forward;
    CWeakObjectPtr<class CBoundInput> m_backward;
    CWeakObjectPtr<class CBoundInput> m_left;
    CWeakObjectPtr<class CBoundInput> m_right;
    void ManageCamera(double DeltaTime);
public:
    void OnConstruct() override;
    void Tick(double DeltaTime) override;
    void PhysicsTick(double PhysicsDeltaTime) override;
};
