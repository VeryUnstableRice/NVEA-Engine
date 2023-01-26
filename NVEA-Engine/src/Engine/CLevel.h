#ifndef CLEVEL_HEADER
#define CLEVEL_HEADER
#include "Engine/CAbstractEngine.h"
#include "Object/CObject.h"

class CLevel : public CObject
{
	std::vector<CObjectPtr<class CEntity>> m_entities;
	std::vector<CObjectPtr<class CPlayer>> m_players;
protected:
	virtual void LevelTick(double DeltaTime) {};
	virtual void LevelPhysicsTick(double DeltaTime) {};
	virtual void OnUnloadedLevel(){};
	virtual void OnLevelChanged(){};
public:
	template<typename type>
	type* SpawnEntity();
	void DestroyEntity(CEntity* entity);

	CPlayer* GetLocalPlayer();
	
	virtual ~CLevel() = default;
	
	void Tick(double deltaTime);
	void PhysicsTick(double FixedDeltaTime);
	void LevelChanged();
	void UnloadedLevel();
};

template <typename type>
type* CLevel::SpawnEntity()
{
	type* entity = CreateObject<type>(false);
	entity->SetLevel(this);
	entity->OnConstruct();
	m_entities.push_back(entity);
	CPlayer* player = dynamic_cast<CPlayer*>(entity);
	if(player)
		m_players.push_back(player);
	return entity;
}

#endif
