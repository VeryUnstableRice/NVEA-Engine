#include "CCameraManager.h"

#include "CCameraEntity.h"

CCameraEntity* CCameraManager::GetCurrentCamera()
{
    return m_cameraEntity;
}

void CCameraManager::SetCurrentCamera(CCameraEntity* entity)
{
    m_cameraEntity = entity;
}
