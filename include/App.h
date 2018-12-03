#pragma once

#include <SDL.h>
#include <Texture.h>
#include <Rasterizer.h>
#include <Scene.h>

class App
{
public:
	App();
	~App();

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Event m_event;
	Texture* m_texture;
	Rasterizer* m_rasterizer;
	Scene* m_scene;

	void Startup();
	void MainLoop();
	void Clear();
	void Render();
};

