#include <Rasterizer.h>


Rasterizer::Rasterizer()
{

}


Rasterizer::~Rasterizer()
{
}

void Rasterizer::RenderScene(Scene * p_Scene, Texture * p_Target, SDL_Renderer* p_Renderer)
{
	int x0 = rand() % 1024;
	int	y0 = rand() % 768;
	int	x1 = rand() % 1024;
	int	y1 = rand() % 768;

	for (int i = 0; i < rand() % 50000 + 1; ++i)
	{
		int dx = abs(x1 - x0);
		int	sx = x0<x1 ? 1 : -1;

		int dy = -abs(y1 - y0);
		int	sy = y0<y1 ? 1 : -1;

		int err = dx + dy;
		int e2;
		SDL_SetRenderDrawColor(p_Renderer, rand() % 255, rand() % 255, rand() % 255, 255);
		for (;;)
		{
			/*SDL_SetRenderDrawColor(p_Renderer, p_Target->m_pixels[x0 + y0 * p_Target->mui_w].ucm_r, 
											   p_Target->m_pixels[x0 + y0 * p_Target->mui_w].ucm_g, 
											   p_Target->m_pixels[x0 + y0 * p_Target->mui_w].ucm_b, 
											   p_Target->m_pixels[x0 + y0 * p_Target->mui_w].ucm_a);*/
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

		x0 = x1;
		y0 = y1;
		x1 = rand() % 1024;
		y1 = rand() % 768;
	}
}
