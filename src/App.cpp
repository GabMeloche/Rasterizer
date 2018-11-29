#include <App.h>
#include <iostream>



App::App()
{
	m_window = SDL_CreateWindow("RASTERIZER",   SDL_WINDOWPOS_CENTERED,
												SDL_WINDOWPOS_CENTERED,
												1024, 768,
												SDL_WINDOW_SHOWN);

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

}


App::~App()
{
}

void App::Startup()
{
	MainLoop();
}

void App::MainLoop()
{
	bool is_over = false;
	while (is_over == false)
	{
		SDL_PollEvent(&m_event);

		if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_ESCAPE)
		{
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			is_over = true;
		}
		Render();
	}
}

void App::Render()
{
	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	SDL_RenderPresent(m_renderer);

}



