#ifndef CTestGameInstance_Header
#define CTestGameInstance_Header
#include "Engine/CAbstractGame.h"

class CTestGameInstance : public CAbstractGame
{
    virtual void GameTick(double DeltaTime) const        override;
    virtual void GamePhysicsTick(double DeltaTime) const override;
public:
    class CShader* DefaultShader;
    class CSound* TestSound = nullptr;
    
    void InitializeAssets() override;
    void UninitiazeGameInstance() override;


    static CTestGameInstance* Instance;
};

#endif