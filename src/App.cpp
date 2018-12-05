#include <App.h>
#include <iostream>
#include <Texture.h>
#include <Rasterizer.h>
#include <Triangle.h>

App::App()
{
	m_window = SDL_CreateWindow("RASTERIZER",   SDL_WINDOWPOS_CENTERED,
												SDL_WINDOWPOS_CENTERED,
												1024, 768,
												SDL_WINDOW_SHOWN);

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_rasterizer = new Rasterizer;
	m_texture = new Texture(1024, 768);
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

		Triangle m_triangle;

		//RED PIXEL
		m_triangle.m_v1.m_position.mf_x = 500;
		m_triangle.m_v1.m_position.mf_y = 200;
		m_texture->m_pixels[500 + 200 * m_texture->mui_w].ucm_r = 255;
		m_texture->m_pixels[500 + 200 * m_texture->mui_w].ucm_g = 0;
		m_texture->m_pixels[500 + 200 * m_texture->mui_w].ucm_b = 0;

		//GREEN PIXEL
		m_triangle.m_v2.m_position.mf_x = 250;
		m_triangle.m_v2.m_position.mf_y = 600;
		m_texture->m_pixels[250 + 600 * m_texture->mui_w].ucm_r = 0;
		m_texture->m_pixels[250 + 600 * m_texture->mui_w].ucm_g = 255;
		m_texture->m_pixels[250 + 600 * m_texture->mui_w].ucm_b = 0;

		//BLUE PIXEL
		m_triangle.m_v3.m_position.mf_x = 750;
		m_triangle.m_v3.m_position.mf_y = 600;
		m_texture->m_pixels[750 + 600 * m_texture->mui_w].ucm_r = 0;
		m_texture->m_pixels[750 + 600 * m_texture->mui_w].ucm_g = 0;
		m_texture->m_pixels[750 + 600 * m_texture->mui_w].ucm_b = 255;


		float invslope1 = (m_triangle.m_v2.m_position.mf_x - m_triangle.m_v1.m_position.mf_x) 
						/ (m_triangle.m_v2.m_position.mf_y - m_triangle.m_v1.m_position.mf_y);

		float invslope2 = (m_triangle.m_v3.m_position.mf_x - m_triangle.m_v1.m_position.mf_x) 
						/ (m_triangle.m_v3.m_position.mf_y - m_triangle.m_v1.m_position.mf_y);

		float curx1 = m_triangle.m_v1.m_position.mf_x;
		float curx2 = m_triangle.m_v1.m_position.mf_x;

		for (int scanlineY = m_triangle.m_v1.m_position.mf_y; scanlineY <= m_triangle.m_v2.m_position.mf_y; scanlineY++)
		{
			//drawLine((int)curx1, scanlineY, (int)curx2, scanlineY);
			m_rasterizer->RenderScene((int)curx1, scanlineY, (int)curx2, scanlineY, *m_texture, m_renderer);
			curx1 += invslope1;
			curx2 += invslope2;
		}

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




