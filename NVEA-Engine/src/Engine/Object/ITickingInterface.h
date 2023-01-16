#pragma once

class ITickingInterface
{
public:
    //should return if the element should tick while paused
    virtual bool ShouldTickWhenPause() const            = 0;
    //returns true if the object should tick always
    virtual bool ShouldTick() const                     = 0;
    //it happens each second
    virtual void Tick(double DeltaTime)                  = 0;
    //it ticks 30 times per minute
    virtual void PhysicsTick(double PhysicsDeltaTime)    = 0;
};
