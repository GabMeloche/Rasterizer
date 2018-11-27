#include <Texture.h>
#include <Color.h>
#include <cassert>

Texture::Texture(unsigned int pui_w, unsigned int pui_h) : mui_w {pui_w}, mui_h {pui_w}
{
	m_pixels = new Color[pui_w * pui_h];

	for (int i = 0; i < pui_w * pui_h; ++i)
	{
		m_pixels[i] = {0, 0, 0, 1};
	}
}

Texture::~Texture()
{
	delete m_pixels;
}

Texture::Texture(const Texture& p_other)
{
	mui_w = p_other.mui_w;
	mui_h = p_other.mui_h;

	m_pixels = new Color[mui_w * mui_h];

	for (int i = 0; i < mui_w * mui_h; ++i)
	{
		m_pixels[i] = p_other.m_pixels[i];
	}

}
void Texture::SetPixelColor(unsigned int pui_x, unsigned int pui_y, const Color& p_c)
{
	assert(pui_x <= mui_w);
	assert(pui_y <= mui_h);

	++pui_y;
	m_pixels[pui_x * pui_y] = p_c;
}