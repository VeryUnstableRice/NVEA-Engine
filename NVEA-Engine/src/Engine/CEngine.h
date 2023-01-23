#ifndef CEngine_Header
#define CEngine_Header
#include "CAbstractEngine.h"

class CEngine : public CAbstractEngine
{
    class CEngineRenderModule* m_renderModule = nullptr;
    class CEngineSoundModule*  m_soundModule = nullptr;
    class CGUIEngineModule*    m_guiModule = nullptr;
    class CInputEngineModule*    m_inputEngineModule = nullptr;
public:
    CEngine();
    virtual ~CEngine();

    void LoadEngine()       override;
    void UnloadEngine()     override;
    
    CEngineRenderModule* GetRenderModule();

    static CEngine* Engine;
};

#endif