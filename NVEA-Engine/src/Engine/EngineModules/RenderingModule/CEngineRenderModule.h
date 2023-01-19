#ifndef CEngineRenderModule_Header
#define CEngineRenderModule_Header
#include "Engine/IEngineModuleInterface.h"
#include "Engine/RenderPipeline/CRenderPipeline.h"

class CEngineRenderModule : public IEngineModuleInterface
{
    CObjectPtr<CRenderPipeline> m_renderPipeline;
public:
    void Tick(double DeltaTime) override;
    bool Load() override;
    void Unload() override;
    std::string ModuleName() override;

    CRenderPipeline* GetRenderPipeline();
};

#endif