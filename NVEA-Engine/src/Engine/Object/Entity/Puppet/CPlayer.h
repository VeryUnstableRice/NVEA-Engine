#ifndef CPlayer_Header
#define CPlayer_Header
#include "Engine/Object/CObject.h"
#include "Engine/Object/Entity/CEntity.h"

class CPlayer : public CEntity
{
    //the entity controlled by the player
    CObjectPtr<class CPuppetEntity> m_puppet;
    bool m_mouseFree;
public:
    CPlayer();
    void SetPuppet(CPuppetEntity* puppet);
    CPuppetEntity* GetPuppet() const;

    void SetMouseFree(bool MouseFree);
    bool IsMouseFree() const;
    
};

#endif