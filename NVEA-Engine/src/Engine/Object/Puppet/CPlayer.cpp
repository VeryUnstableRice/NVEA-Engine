#include "CPlayer.h"

#include "CPuppetEntity.h"

CPlayer::CPlayer()
{
    m_mouseFree = false;
}

void CPlayer::SetPuppet(CPuppetEntity* puppet)
{
    if(m_puppet == puppet) return;
    if(m_puppet) m_puppet->OnPuppeteerChanged(nullptr);
    m_puppet = puppet;
    if(m_puppet) m_puppet->OnPuppeteerChanged(this);
}

CPuppetEntity* CPlayer::GetPuppet() const
{
    return m_puppet.get();
}

void CPlayer::SetMouseFree(bool MouseFree)
{
    m_mouseFree = MouseFree;
}

bool CPlayer::IsMouseFree() const
{
    return m_mouseFree;
}
