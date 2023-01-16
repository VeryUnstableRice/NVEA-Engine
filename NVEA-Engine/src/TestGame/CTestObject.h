#pragma once
#include "Engine/Object/CObject.h"
#include "Engine/Object/ITickingInterface.h"

class CTestObject : public CObject, public ITickingInterface
{
public:
    bool ShouldTickWhenPause() const override;
    bool ShouldTick() const override;
    void Tick(double DeltaTime) override;
    void PhysicsTick(double PhysicsDeltaTime) override;
};
