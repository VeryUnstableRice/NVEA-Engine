#include "CInputManager.h"
#include <iostream>
#include <windows.h>

#include "CBoundInput.h"
#include "Engine/CAbstractGame.h"
#include "Engine/CAbstractEngine.h"
#include "Engine/CEngine.h"
#include "Engine/CLevel.h"
#include "Engine/Object/Puppet/CPlayer.h"

CInputManager::CInputManager()
{
	for (int i = 0; i < m_mouseButtons.size(); ++i)
		m_mouseButtons[i] = false;
	m_centerCursorEvent = CEngine::Engine->GetDynamicHash("center_cursor");
}

void CInputManager::pressKey()
{
	m_keystates = (Uint8*)SDL_GetKeyboardState(&m_numKeys);
}

void CInputManager::releaseKey()
{
	if (m_numKeys)
	{
		if (!m_oldKeystates)
			m_oldKeystates = std::make_unique<Uint8[]>(m_numKeys);

		for (int i = 0; i < m_numKeys; ++i)
			m_oldKeystates[i] = m_keystates[i];
	}
}

bool CInputManager::Update()
{
	CLevel* Level = CAbstractEngine::Engine->GetCurrentLevel();
	if(!Level) return false;
	CPlayer* Player = Level->GetLocalPlayer();
	if(!Player) return false;
	
	SDL_Event event;
	m_mouserel *= 0;
	releaseKey();
	m_mouseButtonsPrevious = m_mouseButtons;

	SDL_SetRelativeMouseMode(Player->IsMouseFree() ? SDL_FALSE : SDL_TRUE);
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return true;
		case SDL_KEYDOWN:
			pressKey();
			break;
		case SDL_KEYUP:
			pressKey();
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_mouseButtons[LeftMouse] = true;
				break;
			case SDL_BUTTON_RIGHT:
				m_mouseButtons[RightMouse] = true;
				break;
			case SDL_BUTTON_MIDDLE:
				m_mouseButtons[MiddleMouse] = true;
				break;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_mouseButtons[LeftMouse] = false;
				break;
			case SDL_BUTTON_RIGHT:
				m_mouseButtons[RightMouse] = false;
				break;
			case SDL_BUTTON_MIDDLE:
				m_mouseButtons[MiddleMouse] = false;
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			if(Player->IsMouseFree()) break;
			CEngine::Engine->CallEvent(m_centerCursorEvent);
			m_mousepos.x = event.motion.x;
			m_mousepos.y = event.motion.y;

			m_mouserel.x = event.motion.xrel;
			m_mouserel.y = event.motion.yrel;
			break;
		}
	}


	return false;
}

glm::ivec2 CInputManager::GetMousePosition()
{
	return m_mousepos;
}

glm::ivec2 CInputManager::GetMouseRelative()
{
	return m_mouserel;
}

void CInputManager::SetMousePosition(glm::ivec2 _pos)
{
	SDL_WarpMouseGlobal(_pos.x, _pos.y);
}

bool CInputManager::KeyStatus(SDL_Scancode key, EButtonEvent event)
{
	switch (event) {
	case EButtonEvent::Down: return KeyDown(key);
	case EButtonEvent::Pressed: return KeyPressed(key);
	case EButtonEvent::Released: return KeyReleased(key);
	}
	return false;
}

bool CInputManager::MouseButtonStatus(EMouseButton key, EButtonEvent event)
{
	switch (event) {
	case EButtonEvent::Down: return MouseButtonDown(key);
	case EButtonEvent::Pressed: return MouseButtonPressed(key);
	case EButtonEvent::Released: return MouseButtonReleased(key);
	}
	return false;
}

CBoundInput* CInputManager::GetInput(const std::string& name, bool create)
{
	for(CObjectPtr<CBoundInput>& Input : m_boundInputs)
		if(Input->GetName() == name)
			return Input.get();
	if(create)
	{
		CObjectPtr<CBoundInput> Input = CreateObject<CBoundInput>()->Init(*this, name);
		m_boundInputs.push_back(Input);
		return Input.get();
	}
	
	return nullptr;
}

bool CInputManager::KeyDown(SDL_Scancode key)
{
	return m_keystates ? m_keystates[key] : false;
}

bool CInputManager::KeyReleased(SDL_Scancode key)
{
	if (!m_keystates || !m_oldKeystates) return false;
	return !m_oldKeystates[key] && m_keystates[key];
}

bool CInputManager::KeyPressed(SDL_Scancode key)
{
	if (!m_keystates || !m_oldKeystates) return false;
	return m_oldKeystates[key] && !m_keystates[key];
}

bool CInputManager::MouseButtonDown(EMouseButton key)
{
	return m_mouseButtons[key];
}

bool CInputManager::MouseButtonPressed(EMouseButton key)
{
	return m_mouseButtons[key] &&  !m_mouseButtonsPrevious[key];
}

bool CInputManager::MouseButtonReleased(EMouseButton key)
{
	return !m_mouseButtons[key] && m_mouseButtonsPrevious[key];
}