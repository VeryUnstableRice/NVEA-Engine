#ifndef CDEBUGLEVEL_HEADER
#define CDEBUGLEVEL_HEADER
#include "CTestObject.h"
#include "CTestPlayerPuppet.h"
#include "Engine/CLevel.h"
#include "Engine/Mesh/CStaticMesh.h"
#include "Engine/Object/CObject.h"

class CDebugLevel : public CLevel
{
    CWeakObjectPtr<class CBoundInput> m_forward;
    CWeakObjectPtr<class CBoundInput> m_backward;
    CWeakObjectPtr<class CBoundInput> m_left;
    CWeakObjectPtr<class CBoundInput> m_right;

    CObjectPtr<CStaticMesh> m_testMesh;
    CObjectPtr<CMeshRenderEntity> m_renderTestMesh;
    CObjectPtr<CTestObject> m_testTickObject;
    CObjectPtr<CTestPlayerPuppet> m_playerPuppet;
public:
    void LevelTick(double DeltaTime) override;
    void LevelPhysicsTick(double DeltaTime) override;
    void OnUnloadedLevel() override;
    void OnLevelChanged() override;
};

#endif
