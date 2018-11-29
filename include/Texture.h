#pragma once
#include <Color.h>
#include <SDL.h>

class Texture
{
public:
	unsigned int mui_w;
	unsigned int mui_h;
	
	Color* m_pcolor;
	SDL_PixelFormat* m_pformat;
	SDL_Surface* m_surface;
	SDL_Texture* m_texture;
	Uint32* m_pixels;
	int m_pitch;

public:
	Texture(unsigned int pui_w, unsigned int pui_h);
	~Texture();
	Texture(const Texture& p_other);

	void SetPixelColor(unsigned int pui_x, unsigned int pui_y, const Color& p_c);
};
