#include "CTestGameInstance.h"

#include "CDebugLevel.h"
#include "Engine/CAbstractEngine.h"
#include "Engine/AssetManager/CAssetManager.h"
#include "Engine/AssetManager/Asset/CShaderAsset.h"
#include "EngineModules/SoundModule/Asset/CSoundAsset.h"

CTestGameInstance* CTestGameInstance::Instance = nullptr;

void CTestGameInstance::GameTick(double DeltaTime) const
{
}

void CTestGameInstance::GamePhysicsTick(double DeltaTime) const
{
}

void CTestGameInstance::InitializeAssets()
{
    Instance = this;
    DefaultShader = CAbstractEngine::Engine->GetAssetManager().CreateAsset<CShaderAsset>("./res/DefaultShader/DefaultShader")->GetAsset();
    TestSound = CAbstractEngine::Engine->GetAssetManager().CreateAsset<CSoundAsset>("./res/untitled.wav")->GetAsset();
    SetLevel(CreateObject<CDebugLevel>());
}

void CTestGameInstance::UninitiazeGameInstance()
{
}
