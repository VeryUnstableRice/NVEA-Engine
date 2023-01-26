#ifndef CRenderPipeline_Header
#define CRenderPipeline_Header
#include <unordered_map>
#include <vector>

#include "Engine/Object/CObject.h"
#include "Engine/MemoryManager/CObjectPtr.h"

class CRenderPipeline : public CObject
{
    using RenderEntitiesVector = std::vector<CWeakObjectPtr<class CMeshRenderEntity>>;
    RenderEntitiesVector m_entities;


    void PrepareForRender();
public:
    CRenderPipeline();
    void Render();

    void Subscribe(class CMeshRenderEntity* Entity);
    void Unsubscribe(class CMeshRenderEntity* Entity);
};

#endif
