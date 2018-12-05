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


void Rasterizer::Convert2Dto3D(Vertex& m_inPoint)
{
	std::cout << m_inPoint.m_position.mf_x << '\n';
	m_inPoint.m_position.mf_x = ((m_inPoint.m_position.mf_x / 5) + 1) * 0.5 * 1024;
	m_inPoint.m_position.mf_y = 768 - ((m_inPoint.m_position.mf_y / 5) + 1) * 0.5 * 768;
	std::cout << m_inPoint.m_position.mf_x << '\n';
}

void Rasterizer::RenderScene(Scene* p_scene, Texture& p_Target, SDL_Renderer* p_Renderer)
{
	float v1x;
	float v1y;
	float v2x;
	float v2y;
	float v3x;
	float v3y;

	for (int i = 0; i < p_scene->getEntities().size(); i++)
	{
		Convert2Dto3D(p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v1);
		Convert2Dto3D(p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v2);
		Convert2Dto3D(p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v3);

		v1x = p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v1.m_position.mf_x;
		v1y = p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v1.m_position.mf_y;
		v2x = p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v2.m_position.mf_x;
		v2y = p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v2.m_position.mf_y;
		v3x = p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v3.m_position.mf_x;
		v3y = p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v3.m_position.mf_y;

		float invslope1 = (v2x - v1x)
						/ (v2y - v1y);

		float invslope2 = (v3x - v1x)
						/ (v3y - v1y);


		float curx1 = v1x;
		float curx2 = v1x;

		for (int scanlineY = v1y; scanlineY <= v2y; scanlineY++)
		{
			int m_width = p_Target.mui_w;

			int x0 = (int)curx1;
			int	y0 = scanlineY;
			int	x1 = (int)curx2;
			int	y1 = scanlineY;

			int dx = abs(x1 - x0);
			int	sx = x0<x1 ? 1 : -1;

			int dy = -abs(y1 - y0);
			int	sy = y0<y1 ? 1 : -1;

			int err = dx + dy;
			int e2;

			//ZBuffer(&p_Target, p_scene);
			//std::cout << p_Target.m_pixels[x0 + y0 * p_Target.mui_w].ucm_r << '\n';
			while(true)
			{
				p_Target.m_pixels[x0 + y0 * m_width].ucm_r = (int)-sqrt(pow(v1x - x0, 2) + pow(v1y - y0, 2)) / 2;
				p_Target.m_pixels[x0 + y0 * m_width].ucm_g = (int)-sqrt(pow(v2x - x0, 2) + pow(v2y - y0, 2)) / 2;
				p_Target.m_pixels[x0 + y0 * m_width].ucm_b = (int)-sqrt(pow(v3x - x0, 2) + pow(v3y - y0, 2)) / 2;

				SDL_SetRenderDrawColor(p_Renderer, p_Target.m_pixels[x0 + y0 * m_width].ucm_r,
					p_Target.m_pixels[x0 + y0 * m_width].ucm_g,
					p_Target.m_pixels[x0 + y0 * m_width].ucm_b,
					p_Target.m_pixels[x0 + y0 * m_width].ucm_a);

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
			curx1 += invslope1;
			curx2 += invslope2;
		}
	}
}

void Rasterizer::ZBuffer(Texture* p_texture, Scene* p_scene)
{
	std::vector<Entity*>& allEntities = p_scene->getEntities();
	float** zBuffer = new float*[1024];
	Color** frameBuffer = new Color*[1024];

	for (size_t i = 0; i < 1024; ++i)
	{
		zBuffer[i] = new float[768];
		frameBuffer[i] = new Color[768];

		for (size_t j = 0; j < 768; ++j)
		{
			zBuffer[i][j] = 0.0f;
			//frameBuffer[i][j] = p_texture->GetPixelColor(i, j);
		}
	}

	for (size_t i = 0; i < allEntities.size(); ++i)
	{
		for (size_t j = 0; j < 1024 * 768; ++j)
		{
			for (size_t k = 0; k < 1024 * 768; ++k)
			{
				float currDepth = allEntities[i]->getMesh()->getVertices()[0].m_position.mf_z;

				if (currDepth > zBuffer[j][k])
				{
					zBuffer[j][k] = currDepth;
					frameBuffer[j][k] = { 255, 255, 255, 255 };
					p_texture->SetPixelColor(j, k, { 255, 255, 255, 255 });
				}
			}
		}
	}
	delete zBuffer;
	delete frameBuffer;
}
