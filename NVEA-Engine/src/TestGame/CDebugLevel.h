#ifndef CDEBUGLEVEL_HEADER
#define CDEBUGLEVEL_HEADER
#include "CTestObject.h"
#include "CTestPlayerPuppet.h"
#include "Engine/CLevel.h"
#include "Engine/Mesh/CStaticMesh.h"
#include "Engine/Object/CObject.h"
#include "EngineModules/SoundModule/CSoundEntity.h"

class CDebugLevel : public CLevel
{
    CObjectPtr<CStaticMesh> m_testMesh;
    CObjectPtr<CMeshRenderEntity> m_renderTestMesh;
    CObjectPtr<CTestObject> m_testTickObject;
    CObjectPtr<CSoundEntity> m_soundEntity;
    CObjectPtr<CTestPlayerPuppet> m_playerPuppet;
public:
    void LevelTick(double DeltaTime) override;
    void LevelPhysicsTick(double DeltaTime) override;
    void OnUnloadedLevel() override;
    void OnLevelChanged() override;
};

#endif
