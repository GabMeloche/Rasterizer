#include <Rasterizer.h>
#include <Vertex.h>
#include <Triangle.h>
#include <iostream>

Rasterizer::Rasterizer()
{

}


Rasterizer::~Rasterizer()
{
}

void Rasterizer::RenderScene(int v0x, int v0y, int v1x, int v1y, Texture& p_Target, SDL_Renderer* p_Renderer)
{
	int x0 = v0x;
	int	y0 = v0y;
	int	x1 = v1x;
	int	y1 = v1y;

	int dx = abs(x1 - x0);
	int	sx = x0<x1 ? 1 : -1;

	int dy = -abs(y1 - y0);
	int	sy = y0<y1 ? 1 : -1;

	int err = dx + dy;
	int e2;

	//std::cout << p_Target.m_pixels[x0 + y0 * p_Target.mui_w].ucm_r << '\n';
	for (;;)
	{
		p_Target.m_pixels[x0 + y0 * p_Target.mui_w].ucm_r = (int)-sqrt(pow(500 - x0, 2) + pow(200 - y0, 2));
		p_Target.m_pixels[x0 + y0 * p_Target.mui_w].ucm_g = (int)-sqrt(pow(250 - x0, 2) + pow(450 - y0, 2));
		p_Target.m_pixels[x0 + y0 * p_Target.mui_w].ucm_b = (int)-sqrt(pow(750 - x0, 2) + pow(450 - y0, 2));

		SDL_SetRenderDrawColor(p_Renderer, p_Target.m_pixels[x0 + y0 * p_Target.mui_w].ucm_r, 
											p_Target.m_pixels[x0 + y0 * p_Target.mui_w].ucm_g, 
											p_Target.m_pixels[x0 + y0 * p_Target.mui_w].ucm_b, 
											p_Target.m_pixels[x0 + y0 * p_Target.mui_w].ucm_a);

		SDL_RenderDrawPoint(p_Renderer, x0, y0);

		if (x0 == x1 && y0 == y1)
			break;

		e2 = 2 * err;

		if (e2 >= dy)
		{
			err += dy; 
			x0 += sx;
		}

		if (e2 <= dx)
		{
			err += dx; 
			y0 += sy;
		}
	}
}
