#ifndef CEngine_Header
#define CEngine_Header
#include "CAbstractEngine.h"
#include "EngineModules/RenderingModule/CEngineRenderModule.h"

class CEngine : public CAbstractEngine
{
    CEngineRenderModule* m_renderModule = nullptr;
public:
    CEngine();
    virtual ~CEngine();

    void LoadEngine()       override;
    void UnloadEngine()     override;
    
    CEngineRenderModule* GetRenderModule();

    static CEngine* Engine;
};

#endif