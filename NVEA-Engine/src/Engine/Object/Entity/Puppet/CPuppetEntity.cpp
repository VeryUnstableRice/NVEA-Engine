#include "CPuppetEntity.h"


void CPuppetEntity::OnPuppeteerChanged(CPlayer* player)
{
    m_player = player;
}

void CPuppetEntity::Tick(double DeltaTime)
{
    CEntity::Tick(DeltaTime);
}

bool CPuppetEntity::IsPlayerOwned()
{
    return m_player;
}
