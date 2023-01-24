#include "CTestGameInstance.h"

#include "CDebugLevel.h"
#include "Engine/CAbstractEngine.h"
#include "Engine/AssetManager/CAssetManager.h"
#include "RenderModule/Assets/CShaderAsset.h"
#include "SoundModule/Asset/CSoundAsset.h"

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
    CAbstractEngine::Engine->CheckForGLErrors();

    DefaultShader = CAbstractEngine::Engine->GetAssetManager().CreateAsset<CShaderAsset>("./res/DefaultShader/DefaultShader")->GetAsset();
    CAbstractEngine::Engine->CheckForGLErrors();

    TestSound = CAbstractEngine::Engine->GetAssetManager().CreateAsset<CSoundAsset>("./res/untitled.wav")->GetAsset();
    CAbstractEngine::Engine->CheckForGLErrors();

    SetLevel(CreateObject<CDebugLevel>());
}

void CTestGameInstance::UninitiazeGameInstance()
{
}
