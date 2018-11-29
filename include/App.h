#pragma once

#include <SDL.h>
#include <Texture.h>

class App
{
public:
	App();
	~App();

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Event m_event;
	Texture* tex;

	void Startup();
	void MainLoop();
	void Clear();
	void Render();
};

