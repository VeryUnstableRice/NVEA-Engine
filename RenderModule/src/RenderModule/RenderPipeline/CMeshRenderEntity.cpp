#include "CMeshRenderEntity.h"

#include "CRenderPipeline.h"
#include "Engine/CEngine.h"
#include "RenderModule/CEngineRenderModule.h"

CMeshRenderEntity::CMeshRenderEntity() : CEntity()
{
}

void CMeshRenderEntity::OnConstruct()
{
    CEntity::OnConstruct();
    CEngineRenderModule::Instance->GetRenderPipeline()->Subscribe(this);
}

void CMeshRenderEntity::OnDestroy()
{
    CEntity::OnDestroy();
    CEngineRenderModule::Instance->GetRenderPipeline()->Unsubscribe(this);
}