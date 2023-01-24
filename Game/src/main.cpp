#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Engine/CAbstractEngine.h"
#include <fenv.h>

#include <limits.h>

#include "CInputEngineModule.h"
#include "Engine/CEngine.h"
#include "Engine/MemoryManager/CMemoryManager.h"
#include "EngineModules/GUIModule/CGUIEngineModule.h"
#include "RenderModule/CEngineRenderModule.h"
#include "SoundModule/CEngineSoundModule.h"
#include "TestGame/CTestGameInstance.h"

#if CHAR_BIT != 8
#error "Char must be 8 bits wide"
#endif

//  m_engineModules.push_back(m_renderModule = new CEngineRenderModule());
//	m_engineModules.push_back(m_soundModule = new CEngineSoundModule());
//	m_engineModules.push_back(m_guiModule = new CGUIEngineModule());
//	m_engineModules.push_back(m_inputEngineModule = new CInputEngineModule());

int main()
{
	CMemoryManager* memory_manager = new CMemoryManager;
	CObjectPtr<CAbstractEngine> engine = CreateObject<CEngine>();
	//we make sure the engine is the last to go
	memory_manager->AddToDeleteLast(engine);
	{
		engine->AddModule(new CEngineRenderModule());
		engine->AddModule(new CEngineSoundModule());
		engine->AddModule(new CGUIEngineModule());
		engine->AddModule(new CInputEngineModule());

		engine->SetLogVerbosity(~0);
		engine->LoadEngine();
		memory_manager->Initialize();

		CObjectPtr<CAbstractGame> game_instance = CreateObject<CTestGameInstance>();
		engine->SetGameInstance(game_instance);
		engine->Run();
	}
	//engine->UnloadEngine();
	delete memory_manager;
	return 0;
}