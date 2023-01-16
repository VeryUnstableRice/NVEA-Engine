#ifndef CGAME_HEADER
#define CGAME_HEADER
#include <chrono>

#include "IEngineModuleInterface.h"
#include "Engine/RenderingObjects/CDisplay.h"
#include "InputManager/CInputManager.h"
#include "MemoryManager/CMemoryManager.h"
#include "RenderPipeline/CRenderPipeline.h"


enum ELogVerbosity : std::uint16_t
{
	NORMAL = 1 << 0,
	GARBAGE_COLLECTOR = 1 << 1,
	GAME_INSTANCE = 1 << 2,
	GL_LOG = 1 << 3,
};

/*
Handles engine specifics, and levels
*/
class CAbstractEngine : public CObject
{
protected:
	double m_deltaTime = 0;
	double m_fixedDeltaTime = 0;
	double m_passedTime = 0;
	std::uint32_t m_tickNum = 0;

	std::uint16_t FixedFPS = 30;
	double FixedMSPerSecond = 0;
	
	CDisplay		m_display;
	CObjectPtr<class CAssetManager>			m_assetManager;
	CObjectPtr<CInputManager>				m_inputManager;
	CObjectPtr<class CAbstractGame> m_gameInstance; //DO NOT USE CREATE A LEVEL HERE WITH NEW
	CObjectPtr<class CAbstractGame> m_abstractGameInstace;

	std::vector<IEngineModuleInterface*> m_engineModules;
	
	std::uint16_t m_verbosity;
	
	void SetFixedFPS(std::uint16_t fps);

	void EngineTick(double deltaTime);
	void EngineFixedTick(double deltaTime);
public:
	CAbstractEngine();
	virtual ~CAbstractEngine();
	void Init(std::string title = "noname");
	void SetResolution(int width, int height);
	void Run();
	std::uint32_t GetTickNum() const;

	virtual void LoadEngine();
	virtual void UnloadEngine();

	void SetLogVerbosity(std::uint16_t Verbosity);

	double GetDeltaTime() const;
	double GetFixedDeltaTime() const;
	double GetPassedTime() const;

	bool IsPaused() const;
	
	void SetGameInstance(CAbstractGame* GameInstance);
	CAbstractGame* GetGameInstance();

	class CLevel* GetCurrentLevel();
	
	CAssetManager& GetAssetManager();
	CInputManager& GetInputManager();

	void PrintLog(const std::string& log, ELogVerbosity Verbosity);

	void CheckForGLErrors();
	
	static CAbstractEngine* Engine;
};

template<typename T>
T* CreateObject(bool CallCtor)
{
    return CMemoryManager::GetInstance()->CreateObject<T>(CallCtor);
}

template<typename T>
T* CreateObject()
{
	return CMemoryManager::GetInstance()->CreateObject<T>(true);
}

inline std::uint32_t CAbstractEngine::GetTickNum() const
{
	return m_tickNum;
}

inline double CAbstractEngine::GetDeltaTime() const
{
	return m_deltaTime;
}

inline double CAbstractEngine::GetFixedDeltaTime() const
{
	return m_fixedDeltaTime;
}

inline double CAbstractEngine::GetPassedTime() const
{
	return m_passedTime;
}

inline CAssetManager& CAbstractEngine::GetAssetManager()
{
	return *m_assetManager.get();
}

#endif
