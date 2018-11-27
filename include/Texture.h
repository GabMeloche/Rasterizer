#pragma once
#include <Color.h>

class Texture
{
private:
	unsigned int mui_w;
	unsigned int mui_h;
	Color* m_pixels;
public:
	Texture(unsigned int pui_w, unsigned int pui_h);
	~Texture();
	Texture(const Texture& p_other);

	void SetPixelColor(unsigned int pui_x, unsigned int pui_y, const Color& p_c);
};
