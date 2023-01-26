#ifndef CCameraManager_Header
#define CCameraManager_Header
#include "Engine/Object/Entity/CEntity.h"

class CCameraManager : public CEntity
{
    CObjectPtr<class CCameraEntity> m_cameraEntity;
public:
    class CCameraEntity* GetCurrentCamera();
    void SetCurrentCamera(class CCameraEntity* entity);
};

#endif