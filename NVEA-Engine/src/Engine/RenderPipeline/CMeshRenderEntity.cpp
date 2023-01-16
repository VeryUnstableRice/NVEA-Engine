#include "CMeshRenderEntity.h"

#include "Engine/CEngine.h"

CMeshRenderEntity::CMeshRenderEntity() : CEntity()
{
}

void CMeshRenderEntity::OnConstruct()
{
    CEntity::OnConstruct();
    CEngine::Engine->GetRenderModule()->GetRenderPipeline()->Subscribe(this);
}

void CMeshRenderEntity::OnDestroy()
{
    CEntity::OnDestroy();
    CEngine::Engine->GetRenderModule()->GetRenderPipeline()->Unsubscribe(this);
}