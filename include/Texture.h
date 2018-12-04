#pragma once
#include <Color.h>
#include <SDL.h>

class Texture
{
public:
	unsigned int mui_w;
	unsigned int mui_h;
	
	Color* m_pixels;

public:

	Texture(unsigned int pui_w, unsigned int pui_h);
	~Texture();
	Texture(const Texture& p_other);

	void SetPixelColor(unsigned int pui_x, unsigned int pui_y, const Color& p_c);
	Color & GetPixelColor(unsigned int pui_x, unsigned int pui_y);
};
