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


void Rasterizer::RenderScene(Scene* p_scene, Texture& p_Target, SDL_Renderer* p_Renderer)
{
	for (int i = 0; i < p_scene->getEntities().size(); i++)
	{

		float invslope1 = (p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v2.m_position.mf_x - p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v1.m_position.mf_x)
						/ (p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v2.m_position.mf_y - p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v1.m_position.mf_y);

		float invslope2 = (p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v3.m_position.mf_x - p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v1.m_position.mf_x)
						/ (p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v3.m_position.mf_y - p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v1.m_position.mf_y);


		float curx1 = p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v1.m_position.mf_x;
		float curx2 = p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v1.m_position.mf_x;

		for (int scanlineY = p_scene->getEntities()[0]->getMesh()->getTriangles()[0].m_v1.m_position.mf_y; scanlineY <= p_scene->getEntities()[0]->getMesh()->getTriangles()[0].m_v2.m_position.mf_y; scanlineY++)
		{
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
			for (;;)
			{
				p_Target.m_pixels[x0 + y0 * p_Target.mui_w].ucm_r = (int)-sqrt(pow(p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v1.m_position.mf_x - x0, 2) + pow(p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v1.m_position.mf_y - y0, 2)) / 2;
				p_Target.m_pixels[x0 + y0 * p_Target.mui_w].ucm_g = (int)-sqrt(pow(p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v2.m_position.mf_x - x0, 2) + pow(p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v2.m_position.mf_y - y0, 2)) / 2;
				p_Target.m_pixels[x0 + y0 * p_Target.mui_w].ucm_b = (int)-sqrt(pow(p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v3.m_position.mf_x - x0, 2) + pow(p_scene->getEntities()[i]->getMesh()->getTriangles()[0].m_v3.m_position.mf_y - y0, 2)) / 2;

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
