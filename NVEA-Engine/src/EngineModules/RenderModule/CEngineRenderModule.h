#ifndef CEngineRenderModule_Header
#define CEngineRenderModule_Header
#include "Engine/IEngineModuleInterface.h"
#include "Engine/MemoryManager/CObjectPtr.h"
#include "RenderingObjects/CDisplay.h"

class CEngineRenderModule : public IEngineModuleInterface
{
    CObjectPtr<class CRenderPipeline> m_renderPipeline;
    CDisplay m_display;
    std::uint64_t m_centerCursorEvent;
public:
    void Tick(double DeltaTime) override;
    bool Load() override;
    void Unload() override;
    std::string ModuleName() override;
    bool Run() override;

    void OnEvent(std::uint64_t eventID) override;
    
    CRenderPipeline* GetRenderPipeline();
    CDisplay& GetDisplay() { return m_display; };
};

#endif