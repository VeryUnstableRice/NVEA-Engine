#include "CEntityComponent.h"

CEntityComponent::CEntityComponent()
{
}

CEntity* CEntityComponent::GetOwner() const
{
    return OwningEntity.get();
}

void CEntityComponent::SetOwner(CEntity* Owner)
{
    OwningEntity = Owner;
}

bool CEntityComponent::ShouldTickWhenPause() const
{
    return false;
}

bool CEntityComponent::ShouldTick() const
{
    return true;
}

void CEntityComponent::Tick(double DeltaTime)
{
}

void CEntityComponent::PhysicsTick(double PhysicsDeltaTime)
{
}
