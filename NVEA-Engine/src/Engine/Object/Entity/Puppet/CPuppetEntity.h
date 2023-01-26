#ifndef CPuppetEntity_Header
#define CPuppetEntity_Header
#include "CPlayer.h"
#include "Engine/Object/Entity/CEntity.h"

class CPuppetEntity : public CEntity
{
    CObjectPtr<CPlayer> m_player = nullptr;
    
public:
    virtual void OnPuppeteerChanged(class CPlayer* player);
    void Tick(double DeltaTime) override;
    bool IsPlayerOwned() override;

    CPlayer* GetPlayer() const;
};

inline CPlayer* CPuppetEntity::GetPlayer() const
{
    return m_player.get();
}

#endif