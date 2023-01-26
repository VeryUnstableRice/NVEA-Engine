#ifndef CEntity_Header
#define CEntity_Header

#include <vector>
#include "Engine/CAbstractEngine.h"
#include "Engine/Object/CObject.h"
#include "Engine/Object/ITickingInterface.h"
#include "EntityComponents/CEntityComponent.h"
#include "EntityComponents/CEntityTransformComponent.h"

class CEntity : public CObject, public ITickingInterface
{
    class CLevel* m_level;
    CEntity* m_parent;
    std::vector<CObjectPtr<CEntity>> m_children;
    std::vector<CObjectPtr<class CEntityComponent>> m_componentsPointers;
    bool m_componentsInitialized = false;
    CObjectPtr<CEntityTransformComponent> m_transformComponent;
protected:
    void RemoveComponent(CEntityComponent* Component);

    template<typename T = CEntityComponent>
    T* CreateComponent()
    {
        T* Component = CreateObject<T>();
        Component->SetOwner(this);
        m_componentsPointers.push_back(Component);
        if(m_componentsInitialized)
            ((CEntityComponent*)(Component))->InitializeComponent();
        return Component;
    }

    void InitializeComponents();
    void DeinitializeComponents();
public:
    CEntity();
    virtual ~CEntity();

    void AttachTo(CEntity* Entity);
    void DeattachFromParent();
    CLevel* GetLevel() const;
    void SetLevel(class CLevel* level);
    void Destroy();

    virtual bool IsPlayerOwned();
    
    void OnConstruct() override;
    void OnDestroy() override;

    bool ShouldTickWhenPause() const override;
    bool ShouldTick() const override;
    void Tick(double DeltaTime) override;
    void PhysicsTick(double PhysicsDeltaTime) override;
    
    CEntityTransformComponent*  GetTransformComponent()     const { return m_transformComponent.get(); }
    CEntity*                    GetEntityParent()           const { return m_parent; }
};

inline CLevel* CEntity::GetLevel() const
{
    return m_level;
}

inline void CEntity::SetLevel(CLevel* level)
{
    m_level = level;
}


#endif
