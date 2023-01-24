#ifndef CAbstract_Header
#define CAbstract_Header
#include <chrono>

#include "IEngineModuleInterface.h"
#include "MemoryManager/CMemoryManager.h"
#include "MemoryManager/CObjectPtr.h"


enum ELogVerbosity : std::uint64_t
{
	NORMAL				= 1 << 0,
	GARBAGE_COLLECTOR	= 1 << 1,
	GAME_INSTANCE		= 1 << 2,
	GL_LOG				= 1 << 3,
	ENGINE_LOADING		= 1 << 4
};

/*
Handles engine specifics, and levels

TODO: -extract the render module from the engine's "kernel"

MODULE AND GAME DO AND DON'Ts:
-The engine may be edited to fit functionality for the game, but it should never have any non virtual references about the modules
-Modules shall call game code
-Game shall never call any other code than itself, in the future once a proper high level is set up this should not even be a problem
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

	std::vector<std::string> m_hashes;
	
	CObjectPtr<class CAssetManager>			m_assetManager;
	CObjectPtr<class CAbstractGame> m_gameInstance; //DO NOT USE CREATE A LEVEL HERE WITH NEW
	CObjectPtr<class CAbstractGame> m_abstractGameInstace;

	std::vector<IEngineModuleInterface*> m_engineModules;
	
	std::uint16_t m_verbosity;
	
	void SetFixedFPS(std::uint16_t fps);

	void EngineTick(double deltaTime);
	void EngineFixedTick(double deltaTime);

	bool RunModules();
public:
	CAbstractEngine();
	virtual ~CAbstractEngine();
	void Run();
	std::uint32_t GetTickNum() const;

	// will return uncollidable hash, but the hash will never be the same between engine runs
	// never use to make actual hashes, just use it to make the code faster by not comparing strings all the time
	std::uint64_t GetDynamicHash(const std::string& hash);

	virtual void LoadEngine();
	virtual void UnloadEngine();

	void SetLogVerbosity(std::uint16_t Verbosity);

	double GetDeltaTime() const;
	double GetFixedDeltaTime() const;
	double GetPassedTime() const;

	void AddModule(IEngineModuleInterface* Module);

	void CallEvent(std::uint64_t event);

	bool IsPaused() const;
	
	void SetGameInstance(CAbstractGame* GameInstance);
	CAbstractGame* GetGameInstance();

	class CLevel* GetCurrentLevel();
	
	CAssetManager& GetAssetManager();

	void PrintLog(const std::string& log, ELogVerbosity Verbosity);

	void CheckForGLErrors();

	const std::vector<IEngineModuleInterface*>& GetEngineModules() const {return m_engineModules; }
	
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

inline void CAbstractEngine::AddModule(IEngineModuleInterface* Module)
{
	m_engineModules.push_back(Module);
}

inline CAssetManager& CAbstractEngine::GetAssetManager()
{
	return *m_assetManager.get();
}


#endif