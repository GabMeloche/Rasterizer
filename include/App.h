#pragma once

#include <SDL.h>

class App
{
public:
	App();
	~App();

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Event m_event;

	void Startup();
	void MainLoop();
	void Render();
};

