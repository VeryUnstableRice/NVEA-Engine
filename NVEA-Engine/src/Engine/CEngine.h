#ifndef CEngine_Header
#define CEngine_Header
#include "CAbstractEngine.h"
#include "EngineModules/GUIModule/CGUIEngineModule.h"
#include "EngineModules/RenderingModule/CEngineRenderModule.h"
#include "EngineModules/SoundModule/CEngineSoundModule.h"

class CEngine : public CAbstractEngine
{
    CEngineRenderModule* m_renderModule = nullptr;
    CEngineSoundModule*  m_soundModule = nullptr;
    CGUIEngineModule*    m_guiModule = nullptr;
public:
    CEngine();
    virtual ~CEngine();

    void LoadEngine()       override;
    void UnloadEngine()     override;
    
    CEngineRenderModule* GetRenderModule();

    static CEngine* Engine;
};

#endif