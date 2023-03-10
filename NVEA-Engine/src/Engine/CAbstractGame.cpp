#include "CAbstractGame.h"
#include "CLevel.h"

CAbstractGame::CAbstractGame()
{
}

void CAbstractGame::Initialize()
{
    InitializeAssets();
}

CLevel* CAbstractGame::GetLevel() const
{
    return m_currentLevel.get();
}

void CAbstractGame::Tick(double DeltaTime) const
{
    GameTick(DeltaTime);
    if(m_currentLevel.get())
        m_currentLevel->Tick(DeltaTime);
}

void CAbstractGame::PhysicsTick(double DeltaTime) const
{
    GamePhysicsTick(DeltaTime);
    if(m_currentLevel.get())
        m_currentLevel->PhysicsTick(DeltaTime);
}

void CAbstractGame::SetLevel(CLevel* level)
{
    if(m_currentLevel) m_currentLevel->UnloadedLevel();
    m_currentLevel = level;
    if(m_currentLevel) m_currentLevel->LevelChanged();
}
