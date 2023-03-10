#include "CDisplay.h"
#include "glad/glad.h"

void CDisplay::Init(std::string title, int width, int height)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

	if (!m_window)
		throw "Could not create window";
	m_context = SDL_GL_CreateContext(m_window);
	if (!m_context)
		throw "Could not make context";

	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
		throw;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SDL_GL_SetSwapInterval(0);
	
	m_running = true;
}

void CDisplay::SetResolution(int width, int height)
{
	SDL_SetWindowSize(m_window, width, height);
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(SDL_GetWindowDisplayIndex(m_window), &DM);
	SDL_SetWindowPosition(m_window, (DM.w - width) * 0.5, (DM.h - height) * 0.5);
}

void CDisplay::Run()
{
	SDL_GL_SwapWindow(m_window);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.45f, 0.5f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CDisplay::CenterCursor()
{
	int width, height;
	SDL_GetWindowSize(m_window, &width, &height);
	SDL_WarpMouseInWindow(m_window, width / 2, height / 2);
}

CDisplay::~CDisplay()
{
	if(m_window) SDL_DestroyWindow(m_window);
}
