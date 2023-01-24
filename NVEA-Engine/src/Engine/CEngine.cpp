#include "CEngine.h"



CEngine* CEngine::Engine = nullptr;

CEngine::CEngine()
{
    Engine = this;
}

CEngine::~CEngine()
{
}

void CEngine::LoadEngine()
{
    CAbstractEngine::LoadEngine();
}

void CEngine::UnloadEngine()
{
    CAbstractEngine::UnloadEngine();
}