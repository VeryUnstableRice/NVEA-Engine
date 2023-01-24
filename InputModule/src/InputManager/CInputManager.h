#ifndef CINPUTMANAGER_HEADER
#define CINPUTMANAGER_HEADER
#include <SDL2/SDL.h>
#include <memory>
#include <array>
#include <string>
#include <vector>

#include "Engine/MemoryManager/CObjectPtr.h"
#include "Engine/Object/CObject.h"
#include <Engine/Math/Math.h>

enum EMouseButton
{
	RightMouse,
	MiddleMouse,
	LeftMouse
};

enum class EButtonEvent : std::uint8_t
{
	Down,
	Pressed,
	Released
};

class CInputManager : public CObject
{
	void pressKey();
	void releaseKey();
	int m_numKeys = 0;
	Uint8* m_keystates = nullptr;
	std::unique_ptr<Uint8[]> m_oldKeystates = nullptr;
	EngineMath::SVector2i m_mousepos, m_mouserel;
	std::array<bool, LeftMouse+1> m_mouseButtons;
	std::array<bool, LeftMouse+1> m_mouseButtonsPrevious;
	bool shouldCenter = false;

	std::uint64_t m_centerCursorEvent;

	bool KeyDown(SDL_Scancode key);
	bool KeyPressed(SDL_Scancode key);
	bool KeyReleased(SDL_Scancode key);

	bool MouseButtonDown(EMouseButton key);
	bool MouseButtonPressed(EMouseButton key);
	bool MouseButtonReleased(EMouseButton key);

	std::vector<CObjectPtr<class CBoundInput>> m_boundInputs;
public:
	CInputManager();
	bool Update();

	const EngineMath::SVector2i& GetMousePosition() const;
	const EngineMath::SVector2i& GetMouseRelative() const;
	void SetMousePosition(EngineMath::SVector2i _pos);
	
	bool KeyStatus(SDL_Scancode key, EButtonEvent event);
	bool MouseButtonStatus(EMouseButton key, EButtonEvent event);

	CBoundInput* GetInput(const std::string& name, bool create = false);
};

inline const EngineMath::SVector2i& CInputManager::GetMousePosition() const
{
	return m_mousepos;
}

inline const EngineMath::SVector2i& CInputManager::GetMouseRelative() const
{
	return m_mouserel;
}

#endif