#include <Texture.h>
#include <Color.h>
#include <cassert>
#include <iostream>

Texture::Texture(unsigned int pui_w, unsigned int pui_h) : mui_w {pui_w}, mui_h {pui_w}
{
	m_pcolor = new Color[pui_w * pui_h];

	for (unsigned int i = 0; i < pui_w * pui_h; ++i)
	{
		m_pcolor[i] = {0, 0, 0, 1};
	}
}

Texture::~Texture()
{
	delete m_pcolor;
}

Texture::Texture(const Texture& p_other)
{
	mui_w = p_other.mui_w;
	mui_h = p_other.mui_h;

	m_pcolor = new Color[mui_w * mui_h];

	for (unsigned int i = 0; i < mui_w * mui_h; ++i)
	{
		m_pcolor[i] = p_other.m_pcolor[i];
	}

}

// pui_x and pui_y go from 0 to mui_x -1 / mui_y - 1. First index is 0, 0 and last index is mui_x - 1, mui_y - 1
void Texture::SetPixelColor(unsigned int pui_x, unsigned int pui_y, const Color& p_c)
{
	assert(pui_x < mui_w);
	assert(pui_y < mui_h);
	unsigned int tmp = 10;

	if (pui_y == 0)
		tmp = 1;

	m_pcolor[pui_x + pui_y * tmp] = p_c;
}