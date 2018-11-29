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
	Clear();

	tex = new Texture(1024, 768);
	SDL_Color* color;

	Uint32 rmask, gmask, bmask, amask;

	if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;

	}
	else
	{
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	}

	tex->m_surface = SDL_CreateRGBSurface(0, tex->mui_w, tex->mui_h, 8, 0, 0, 0, 0);
	
	if (tex->m_surface == nullptr) {
		std::cout << "Surface NULL\n";
	}
	tex->m_pformat = tex->m_surface->format;

	if (tex->m_pformat->BitsPerPixel != 8) {
		std::cout << "Not an 8-bit surface.\n";
	}
	
	SDL_LockSurface(tex->m_surface);
	tex->m_pixels = (Uint32*)tex->m_surface->pixels;
	//[(400 * tex->m_surface->w) + 600];

	Uint32 *target_pixel = tex->m_pixels + 400 * tex->m_surface->w +
		600 * sizeof *target_pixel;

	Uint32 pixel = 0xff000000;

	*target_pixel = pixel;

	//color = &tex->m_pformat->palette->colors[(Uint8)index];
	SDL_UnlockSurface(tex->m_surface);

	//SDL_CreateTextureFromSurface(m_renderer, tex->m_surface);

	//std::cout << "Pixel color:" << (int)color->r << ' ' << (int)color->g << ' ' << (int)color->b << '\n';
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
		SDL_RenderCopy(m_renderer, tex->m_texture, nullptr, nullptr);
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



