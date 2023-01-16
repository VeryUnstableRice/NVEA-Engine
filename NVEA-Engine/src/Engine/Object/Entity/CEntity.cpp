#include "CEntity.h"

#include "Engine/CLevel.h"
#include "Engine/Object/Puppet/CPuppetEntity.h"


CEntity::CEntity()
{
    
}

CEntity::~CEntity()
{
    
}

void CEntity::AttachTo(CEntity* Entity)
{
    if(Entity == m_parent) return;
    DeattachFromParent();
    m_parent = Entity;
    Entity->m_children.push_back(this);
}

void CEntity::DeattachFromParent()
{
    if(!m_parent) return;
    for(std::uint16_t i = 0; i < m_parent->m_children.size(); ++i)
    {
        if(m_parent->m_children[i] != this) continue;
        m_parent->m_children.erase(m_parent->m_children.begin()+i);
        break;
    }
    m_parent = nullptr;
}

void CEntity::PrintLocation()
{
    std::string str = GetTransformComponent()->GetWorldTransform().to_string();
    CAbstractEngine::Engine->PrintLog(GetObjectName() + str, NORMAL);
}

bool CEntity::IsPlayerOwned()
{
    if(m_parent && m_parent->IsPlayerOwned()) return true;
    return false;
}

void CEntity::Destroy()
{
    m_level->DestroyEntity(this);
    MarkForDestruction();
}

void CEntity::OnConstruct()
{
    CObject::OnConstruct();
    m_transformComponent = CreateComponent<CEntityTransformComponent>();
}

void CEntity::OnDestroy()
{
    CObject::OnDestroy();
}

bool CEntity::ShouldTickWhenPause() const
{
    return true;
}

bool CEntity::ShouldTick() const
{
    return true;
}

void CEntity::Tick(double DeltaTime)
{
}

void CEntity::PhysicsTick(double PhysicsDeltaTime)
{
}


void CEntity::RemoveComponent(CEntityComponent* Component)
{
    std::erase(m_componentsPointers, Component);
}