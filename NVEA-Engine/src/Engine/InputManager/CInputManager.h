#ifndef CINPUTMANAGER_HEADER
#define CINPUTMANAGER_HEADER
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <memory>
#include <array>
#include <string>
#include <vector>

#include "Engine/MemoryManager/CObjectPtr.h"
#include "Engine/Object/CObject.h"

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
	glm::ivec2 m_mousepos, m_mouserel;
	std::array<bool, LeftMouse+1> m_mouseButtons;
	std::array<bool, LeftMouse+1> m_mouseButtonsPrevious;
	bool shouldCenter = false;

	bool KeyDown(SDL_Scancode key);
	bool KeyPressed(SDL_Scancode key);
	bool KeyReleased(SDL_Scancode key);

	bool MouseButtonDown(EMouseButton key);
	bool MouseButtonPressed(EMouseButton key);
	bool MouseButtonReleased(EMouseButton key);

	std::vector<CObjectPtr<class CBoundInput>> m_boundInputs;
public:
	CInputManager();
	bool Update(SDL_Window* window);

	glm::ivec2 GetMousePosition();
	glm::ivec2 GetMouseRelative();
	void SetMousePosition(glm::ivec2 _pos);
	void CenterMouse();

	bool KeyStatus(SDL_Scancode key, EButtonEvent event);
	bool MouseButtonStatus(EMouseButton key, EButtonEvent event);

	CBoundInput* GetInput(const std::string& name, bool create = false);
};

#endif