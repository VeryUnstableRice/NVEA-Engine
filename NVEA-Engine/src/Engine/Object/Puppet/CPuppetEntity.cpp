#include "CPuppetEntity.h"

void CPuppetEntity::ManageInput(CInputManager* input_manager)
{
    
}

void CPuppetEntity::OnPuppeteerChanged(CPlayer* player)
{
    m_player = player;
}

void CPuppetEntity::Tick(double DeltaTime)
{
    CEntity::Tick(DeltaTime);
    if(m_player)
    {
        ManageInput(&CAbstractEngine::Engine->GetInputManager());
    }
}

bool CPuppetEntity::IsPlayerOwned()
{
    return m_player;
}
