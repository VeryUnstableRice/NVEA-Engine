#include "CLevel.h"
#include "Engine/Object/Entity/Puppet/CPlayer.h"

void CLevel::DestroyEntity(CEntity* entity)
{
    std::erase(m_entities, entity);
}

CPlayer* CLevel::GetLocalPlayer()
{
    if(m_players.empty()) return nullptr;
    return m_players[0].get();
}

void CLevel::Tick(double deltaTime)
{
    LevelTick(deltaTime);
}

void CLevel::PhysicsTick(double FixedDeltaTime)
{
    LevelPhysicsTick(FixedDeltaTime);
}

void CLevel::LevelChanged()
{
    for(CObjectPtr<CPlayer>& player : m_players)
        player->Destroy();
    m_players.clear();
    SpawnEntity<CPlayer>();

    OnLevelChanged();
}

void CLevel::UnloadedLevel()
{
    OnUnloadedLevel();
}
