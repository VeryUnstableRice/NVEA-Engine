#ifndef IAbstractGameInstance_Header
#define IAbstractGameInstance_Header
#include "Object/CObject.h"
#include "MemoryManager/CObjectPtr.h"

class CAbstractGame : public CObject
{
    CObjectPtr<class CLevel>            m_currentLevel;
    CObjectPtr<class CCameraManager>    m_cameraManager;
protected:
    void SetLevel(CLevel* level);

    virtual void GameTick(double DeltaTime) const        = 0;
    virtual void GamePhysicsTick(double DeltaTime) const = 0;
public:
    CAbstractGame();

    void Initialize();
    virtual void InitializeAssets()                     = 0;
    virtual void UninitiazeGameInstance()               = 0;
    
    virtual CLevel*         GetLevel() const;
    virtual CCameraManager* GetCameraManager() const;
    
    void Tick(double DeltaTime) const;
    void PhysicsTick(double DeltaTime) const;
};

#endif