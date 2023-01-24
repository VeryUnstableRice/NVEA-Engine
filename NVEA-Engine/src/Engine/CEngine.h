#ifndef CEngine_Header
#define CEngine_Header
#include "CAbstractEngine.h"

class CEngine : public CAbstractEngine
{
public:
    CEngine();
    virtual ~CEngine();

    void LoadEngine()       override;
    void UnloadEngine()     override;

    static CEngine* Engine;
};

#endif