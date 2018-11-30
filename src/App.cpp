#include <App.h>
#include <iostream>
#include <Texture.h>


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
		Clear();
		if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_ESCAPE || m_event.type == SDL_QUIT)
		{
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			is_over = true;
		}
		Test();
		Render();
	}
}
void App::Clear()
{
	SDL_SetRenderDrawColor(m_renderer, 25, 25, 25, 255);
	SDL_RenderClear(m_renderer);
}
void App::Render()
{
	SDL_RenderPresent(m_renderer);
}

void App::Test()
{
	int x0 = 1000;
	int	y0 = 300;
	int	x1 = 300;
	int	y1 = 450;

	int dx = abs(x1 - x0), sx = x0<x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0<y1 ? 1 : -1;
	int err = dx + dy, e2; /* error value e_xy */

	for (;;) {  /* loop */
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderDrawPoint(m_renderer, x0, y0);
		
		if (x0 == x1 && y0 == y1) 
			break;
		
		e2 = 2 * err;

		if (e2 >= dy) 
		{ 
			err += dy; x0 += sx; 
		} 
		/* e_xy+e_x > 0 */
		if (e2 <= dx) 
		{ 
			err += dx; y0 += sy; 
		} 
		/* e_xy+e_y < 0 */
	}
}



