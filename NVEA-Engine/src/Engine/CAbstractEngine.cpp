#include "CAbstractEngine.h"
#include "CLevel.h"
#include <chrono>
#include <iostream>
#include <glad/glad.h>

#include "AssetManager/CAssetManager.h"
#include "CAbstractGame.h"
#include "Object/ITickingInterface.h"

CAbstractEngine* CAbstractEngine::Engine = nullptr;

void CAbstractEngine::SetFixedFPS(std::uint16_t fps)
{
	FixedFPS = fps;
	FixedMSPerSecond = 1.0 / (FixedFPS+1);
}

void CAbstractEngine::EngineTick(double deltaTime)
{
	for(IEngineModuleInterface* module : m_engineModules)
		module->Tick(deltaTime);
	
	if(m_gameInstance)
		m_gameInstance->Tick(deltaTime);
	for(ObjectIterator It; It; ++It)
	{
		ITickingInterface* Interface = dynamic_cast<ITickingInterface*>(&*It);
		if(Interface && (Interface->ShouldTick() || (Interface->ShouldTickWhenPause() && CAbstractEngine::Engine->IsPaused())))
			Interface->Tick(deltaTime);
	}
}

void CAbstractEngine::EngineFixedTick(double deltaTime)
{
	if(m_gameInstance)
		m_gameInstance->PhysicsTick(deltaTime);
	for(ObjectIterator It; It; ++It)
	{
		ITickingInterface* Interface = dynamic_cast<ITickingInterface*>(&*It);
		if(Interface && (Interface->ShouldTick() || (Interface->ShouldTickWhenPause() && CAbstractEngine::Engine->IsPaused())))
			Interface->PhysicsTick(deltaTime);
	}
}

bool CAbstractEngine::RunModules()
{
	bool run = false;
	bool force_exit = false;
	for(IEngineModuleInterface* module : m_engineModules)
	{
		run |= module->Run();
		force_exit |= module->ForceExit();
	}
	return run && !force_exit;
}

CAbstractEngine::CAbstractEngine() 
{
	Engine = this;
	m_verbosity = 0;
}

CAbstractEngine::~CAbstractEngine()
{
	SetGameInstance(nullptr);
	UnloadEngine();
}

void CAbstractEngine::Run()
{
	auto begin = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	
	auto now_fixed = std::chrono::high_resolution_clock::now();
	auto last_fixed = std::chrono::high_resolution_clock::now();
	while(RunModules())
	{
		//fixed delta time
		now_fixed = std::chrono::high_resolution_clock::now();
		double elapsed_fixed = std::chrono::duration<double>(now_fixed - last_fixed).count();
		if (elapsed_fixed >= FixedMSPerSecond)
		{
			EngineFixedTick(elapsed_fixed);
			last_fixed = std::chrono::high_resolution_clock::now();
		}
		
		//normal tick
		end = std::chrono::high_resolution_clock::now();
		m_deltaTime = std::chrono::duration<double>(end - begin).count();
		begin = end;
		m_passedTime += m_deltaTime;
		if (m_gameInstance && m_deltaTime > 0 && m_deltaTime <= 1)
		{
			EngineTick(m_deltaTime);
			++m_tickNum;
		}
	}
}

std::uint64_t CAbstractEngine::GetDynamicHash(const std::string& hash)
{
	for(std::string& current : m_hashes)
	{
		if(current != hash) continue;
		return reinterpret_cast<std::uint64_t>(&current);
	}

	m_hashes.push_back(hash);
	return reinterpret_cast<std::uint64_t>(&m_hashes.back());
}

void CAbstractEngine::LoadEngine()
{
	m_assetManager = CreateObject<CAssetManager>();
	for(IEngineModuleInterface* module : m_engineModules)
	{
		std::string Result = module->Load() ? "has been loaded successfully" : "has failed to load";
		PrintLog(module->ModuleName() + " " + Result, ELogVerbosity::ENGINE_LOADING);
	}
}

void CAbstractEngine::UnloadEngine()
{
	for(IEngineModuleInterface* module : m_engineModules)
	{
		module->Unload();
		delete module;
	}
	m_engineModules.clear();
}

void CAbstractEngine::SetLogVerbosity(std::uint16_t Verbosity)
{
	m_verbosity = Verbosity;
}

void CAbstractEngine::CallEvent(std::uint64_t event)
{
	for(IEngineModuleInterface* module : m_engineModules)
	{
		module->OnEvent(event);
	}
}

bool CAbstractEngine::IsPaused() const
{
	return false;
}

void CAbstractEngine::SetGameInstance(CAbstractGame* GameInstance)
{
	if(m_gameInstance == GameInstance) return;
	
	if(m_gameInstance)
	{
		m_gameInstance->UninitiazeGameInstance();
		PrintLog("Unloading game instance", ELogVerbosity::GAME_INSTANCE);
	}
	m_gameInstance = GameInstance;
	if(m_gameInstance)
	{
		m_gameInstance->Initialize();
		PrintLog("Loading game instance", ELogVerbosity::GAME_INSTANCE);
	}
}

CAbstractGame* CAbstractEngine::GetGameInstance()
{
	return m_gameInstance.get();
}

CLevel* CAbstractEngine::GetCurrentLevel()
{
	CAbstractGame* Game = Engine->GetGameInstance();
	if(!Game) return nullptr;
	CLevel* Level = Game->GetLevel();
	return Level;
}

void CAbstractEngine::PrintLog(const std::string& log, ELogVerbosity Verbosity)
{
	if(!(m_verbosity & static_cast<std::uint16_t>(Verbosity))) return;
	time_t t = std::time(nullptr);
	std::ostringstream oss;
	tm tm{};
	localtime_s(&tm, &t);  // NOLINT(cert-err33-c)
	std::cout << "[" << std::put_time(&tm, "%d/%m/%Y %H:%M:%S") << "] " << log << std::endl;
}

void CAbstractEngine::CheckForGLErrors()
{
	GLenum err;
	while((err = glGetError()) != GL_NO_ERROR)
	{
		PrintLog("GLError: " + std::to_string(err), GL_LOG);
	}
}
