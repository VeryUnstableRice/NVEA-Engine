#ifndef CDISPLAY_HEADER
#define CDISPLAY_HEADER

#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "Engine/InputManager/CInputManager.h"

struct sdl_window_deleter
{
	void operator()(SDL_Window* p) const { SDL_DestroyWindow(p); }
};

class CDisplay
{
	SDL_Window *m_window = nullptr;
	SDL_GLContext m_context = nullptr;
	bool m_running = false;
public:
	void Init(std::string title, int width, int height);
	void SetResolution(int width, int height);
	bool Run(CInputManager& InputManager);
	~CDisplay();
};

#endif