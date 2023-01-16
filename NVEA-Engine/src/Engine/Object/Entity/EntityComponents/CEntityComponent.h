#ifndef CEntityComponent_Header
#define CEntityComponent_Header
#include "Engine/Object/CObject.h"
#include "Engine/Object/ITickingInterface.h"
#include "Engine/MemoryManager/CObjectPtr.h"

//Abstract class
class CEntityComponent : public CObject, public ITickingInterface
{
    CWeakObjectPtr<class CEntity> OwningEntity = nullptr;
public:
    CEntityComponent();
    CEntity* GetOwner() const;
    void SetOwner(CEntity* Owner);

    bool ShouldTickWhenPause() const override;
    bool ShouldTick() const override;
    void Tick(double DeltaTime) override;
    void PhysicsTick(double PhysicsDeltaTime) override;
};

#endif