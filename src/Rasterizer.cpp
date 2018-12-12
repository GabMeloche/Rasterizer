#include <Rasterizer.h>
#include <Vertex.h>
#include <Triangle.h>
#include <Math/Vector/Vec3.h>
#include <iostream>


Mat4 Ortho;
float p = 0;

Rasterizer::Rasterizer()
{

	m_zBuffer = new float*[1024];

	for (size_t i = 0; i < 1024; ++i)
	{
		m_zBuffer[i] = new float[768];

		for (size_t j = 0; j < 768; ++j)
		{
			m_zBuffer[i][j] = 0.0f;
		}
	}
}


Rasterizer::~Rasterizer()
{
	delete m_zBuffer;
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
	p += 3;
	float x1;
	float y1;
	float x2;
	float y2;
	float finalZ = 0;
	//FOR EACH MESH
	for (int i = 0; i < p_scene->getEntities().size(); i++)
	{
		//FOR EACH TRIANGLE IN THE MESH
		for (int k = 0; k < p_scene->getEntities()[i]->getMesh()->getTriangles().size(); ++k)
		{
			int m_width = p_Target.mui_w;

			//LOOP FOR EACH LINE OF THE TRIANGLE
			for (int j = 0; j < 3; ++j)
			{
				Mat4 Scale;
				Scale = Mat4::CreateScaleMatrix(1);

				Mat4 Ortho;
				Ortho = Mat4::Vec2dOrtho(*p_scene->getEntities()[i]->getMesh()->getTriangles()[k][j].m_pos);

				Mat4 Rotation;
				Rotation = Mat4::CreateRotationMatrix(p, 1, 1, 1);

				Vec4 tmpPos1 = *p_scene->getEntities()[i]->getMesh()->getTriangles()[k][j].m_pos;
				tmpPos1 = Ortho * Rotation * Scale * tmpPos1;

				Vec4 tmpPos2 = *p_scene->getEntities()[i]->getMesh()->getTriangles()[k][j + 1].m_pos;
				tmpPos2 = Ortho * Rotation * Scale * tmpPos2;

				
				x1 = tmpPos1.mf_x;
				y1 = tmpPos1.mf_y;


				x2 = tmpPos2.mf_x;
				y2 = tmpPos2.mf_y;

				const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
				if (steep)
				{
					std::swap(x1, y1);
					std::swap(x2, y2);
				}

				if (x1 > x2)
				{
					std::swap(x1, x2);
					std::swap(y1, y2);
				}

				const float dx = x2 - x1;
				const float dy = fabs(y2 - y1);

				float error = dx / 2.0f;
				const int ystep = (y1 < y2) ? 1 : -1;
				int y = (int)y1;

				const int maxX = (int)x2;

				for (int x = (int)x1; x < maxX; x++)
				{
					if (steep)
					{
						SDL_SetRenderDrawColor(p_Renderer, 255, 0, 255, 255);
						SDL_RenderDrawPoint(p_Renderer, y, x);
					}
					else
					{
						SDL_SetRenderDrawColor(p_Renderer, 0, 255, 255, 255);
						SDL_RenderDrawPoint(p_Renderer, x, y);
					}

					error -= dy;
					if (error < 0)
					{
						y += ystep;
						error += dx;
					}
				}
			}
		}
	}
}

//TODO: ZBuffer must take a single pixel as parameter, and must be called to draw every pixel (not the whole screen at once)

void Rasterizer::ZBuffer(unsigned int p_x, unsigned int p_y, Triangle& p_triangle, Texture& p_texture)
{
	static unsigned int color = 0;
	Vec3 v0 = { p_triangle.m_v2.m_position - p_triangle.m_v1.m_position };
	Vec3 v1 = { p_triangle.m_v3.m_position - p_triangle.m_v1.m_position };

	float u = v0.GetMagnitude();
	float v = v1.GetMagnitude();

	Vec3 vMult0 = v0 * u;
	Vec3 vMult1 = v1 * v;

	Vec3 Point = p_triangle.m_v1.m_position;
	Point = Point + vMult1;

	if (m_zBuffer[p_x][p_y] < Point.mf_z)
	{
		m_zBuffer[p_x][p_y] = Point.mf_z;

		p_texture.SetPixelColor(p_x, p_y, { color, 0, 0, 255 });
		++color;
		
		if (color == 255)
			color = 0;
	}
}
	
	
	
	
	
	
	
	
	
	/*std::vector<Entity*>& allEntities = p_scene->getEntities();
	size_t eSize = allEntities.size();
	
	for (size_t i = 0; i < eSize; ++i)
	{
		const std::vector<Triangle>& triangles = allEntities[i]->getMesh()->getTriangles();

		for (size_t j = 0; j < triangles.size(); ++j)
		{
			for (unsigned int k = 0; k < 3; ++k)
			{
				//'[]' operator overloaded on triangles to return 1 of 3 vertices of triangle
				if (triangles[j][k].m_position.mf_z > m_zBuffer[p_x][p_y])
				{
					m_zBuffer[p_x][p_y] = triangles[j][k].m_position.mf_z;
				}
>>>>>>> 8a76519fdb5ec9a6c7589411bce1b06afe177389
			}

		}
	}

	/*for (size_t i = 0; i < size; ++i)
	{
		float currDepth = allEntities[i]->getMesh()->getTriangles()[0].m_v1.m_position.mf_z;
		float* triangleZone = allEntities[i]->CheckTriangleZone();

		for (size_t j = triangleZone[0]; j < triangleZone[1]; ++j)
		{
			for (size_t k = triangleZone[2]; k < triangleZone[3]; ++k)
			{

				if (currDepth > m_zBuffer[j][k])
				{
					m_zBuffer[j][k] = currDepth;

					if (i == 0)
						p_texture->SetPixelColor(j, k, { 0, 0, 255, 255 });
					else
						p_texture->SetPixelColor(j, k, { 255, 0, 0, 255 });
				}
			}
		}
	}*/
