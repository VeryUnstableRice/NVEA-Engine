#ifndef CEngineRenderModule_Header
#define CEngineRenderModule_Header
#include "Engine/IEngineModuleInterface.h"
#include "Engine/RenderPipeline/CRenderPipeline.h"

class CEngineRenderModule : public IEngineModuleInterface
{
    CObjectPtr<CRenderPipeline> m_renderPipeline;
public:
    void Tick(double DeltaTime) override;
    void Load() override;
    void Unload() override;

    CRenderPipeline* GetRenderPipeline();
};

#endif