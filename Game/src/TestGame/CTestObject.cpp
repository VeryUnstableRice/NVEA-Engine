#include "CTestObject.h"

#include "Engine/CAbstractEngine.h"

bool CTestObject::ShouldTickWhenPause() const
{
    return false;
}

bool CTestObject::ShouldTick() const
{
    return true;
}

void CTestObject::Tick(double DeltaTime)
{
    CAbstractEngine::Engine->PrintLog("Ticking", NORMAL);
}

void CTestObject::PhysicsTick(double PhysicsDeltaTime)
{
}
