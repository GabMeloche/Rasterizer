#include <Rasterizer.h>
#include <Vertex.h>
#include <Triangle.h>
#include <Math/Vector/Vec3.h>
#include <iostream>
#include <algorithm>


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

void Rasterizer::setTexture(Texture* p_texture)
{
	m_texture = p_texture;
}

void Rasterizer::Convert2Dto3D(Vertex& m_inPoint)
{
	std::cout << m_inPoint.m_position.mf_x << '\n';
	m_inPoint.m_position.mf_x = ((m_inPoint.m_position.mf_x / 5) + 1) * 0.5 * 1024;
	m_inPoint.m_position.mf_y = 768 - ((m_inPoint.m_position.mf_y / 5) + 1) * 0.5 * 768;
	std::cout << m_inPoint.m_position.mf_x << '\n';
}

void Rasterizer::RenderScene(Scene* p_scene, Texture& p_Target)
{
	p += 2;

	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	std::vector<Entity*>& allEntities = p_scene->getEntities();
	size_t eSize = allEntities.size();
	float finalZ = 0.0f;
	
	ClearZBuffer();
	//FOR EACH MESH
	for (size_t i = 0; i < eSize; i++)
	{
		size_t tSize = allEntities[i]->getMesh()->getTriangles().size();
		//FOR EACH TRIANGLE IN THE MESH
		for (size_t k = 0; k < tSize; ++k)
		{
			int m_width = p_Target.mui_w;
			Triangle& currTriangle = p_scene->getEntities()[i]->getMesh()->getTriangles()[k];
			//Transformation Matrix
			Mat4 Translation;
			Translation = Mat4::CreateTranslationMatrix({ 0.0f, 0.0f, 0.0f });

			Mat4 Rotation;
			Rotation = Mat4::CreateRotationMatrix(p, 0, 1, 1);

			Mat4 Scale;
			Scale = Mat4::CreateScaleMatrix(0.8f);

			Mat4 TransformMat;
			TransformMat = Translation * Rotation * Scale;


			//LOOP FOR EACH LINE OF THE TRIANGLE
			for (int j = 0; j < 3; ++j)
			{
				float distance = 10 ;
				finalZ = 1.0f / (distance - currTriangle[j].m_pos->mf_z);

				float OrthoMatrix[4][4] = {
				{ 1,0.0f,0.0f,0.0f },
				{ 0.0f,1,0.0f,0.0f },
				{ 0.0f,0.0f,finalZ,0.0f },
				{ 0.0f,0.0f,0.0f,1.0f}
				};
				Ortho.SetMatrix(OrthoMatrix);

				Vec4 tmpPos1 = *currTriangle[j].m_pos;
				tmpPos1 = TransformMat * tmpPos1;
				tmpPos1 = Ortho * tmpPos1;

				Vec4 tmpPos2 = *currTriangle[j + 1].m_pos;
				tmpPos2 = TransformMat * tmpPos2;
				tmpPos2 = Ortho * tmpPos2;

				Vec4 tmpPos3 = *currTriangle[j + 2].m_pos;
				tmpPos3 = TransformMat * tmpPos3;
				tmpPos3 = Ortho * tmpPos3;


				Vec3 newVecPos1 = GetPixelPos(tmpPos1);
				Vec3 newVecPos2 = GetPixelPos(tmpPos2);
				Vec3 newVecPos3 = GetPixelPos(tmpPos3);
				x1 = newVecPos1.mf_x;
				y1 = newVecPos1.mf_y;

				x2 = newVecPos2.mf_x;
				y2 = newVecPos2.mf_y;

				x3 = newVecPos3.mf_x;
				y3 = newVecPos3.mf_y;

				Vec3 v1 = newVecPos1;
				Vec3 v2 = newVecPos2;
				Vec3 v3 = newVecPos3;

				FillTriangles(v1, v2, v3);
				/*const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
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
				int y = static_cast<int>(y1);

				const int maxX = static_cast<int>(x2);

				for (int x = static_cast<int>(x1); x < maxX; x++)
				{
						ZBuffer(x, y, currTriangle, p_Target);
						SDL_SetRenderDrawColor(p_renderer, p_Target.m_pixels[x + y * p_Target.mui_w].ucm_r, p_Target.m_pixels[x + y * p_Target.mui_w].ucm_g, p_Target.m_pixels[x + y * p_Target.mui_w].ucm_b, 255);
						SDL_RenderDrawPoint(p_renderer, x, y);

					error -= dy;
					if (error < 0)
					{
						y += ystep;
						error += dx;
					}
				}*/
			}
		}
	}
}

void Rasterizer::ZBuffer(unsigned int p_x, unsigned int p_y, Triangle& p_triangle, Texture* p_texture)
{
	Vec3 v0 = { p_triangle.m_v2.m_position - p_triangle.m_v1.m_position };
	Vec3 v1 = { p_triangle.m_v3.m_position - p_triangle.m_v1.m_position };

	float u = v0.GetMagnitude();
	float v = v1.GetMagnitude();

	Vec3 vMult0 = v0 * u;
	Vec3 vMult1 = v1 * v;

	Vec3 Point1 = p_triangle.m_v1.m_position;
	Vec3 Point2 = p_triangle.m_v2.m_position;
	Vec3 Point3 = p_triangle.m_v3.m_position;
	Point1 = Point1 + vMult1;
	Point2 = Point2 + vMult1;
	Point3 = Point3 + vMult1;

	if (m_zBuffer[p_x][p_y] < Point1.mf_z)
	{
		m_zBuffer[p_x][p_y] = Point1.mf_z;
		p_texture->SetPixelColor(p_x, p_y, p_triangle.m_v1.m_color);
	}
	else if (m_zBuffer[p_x][p_y] < Point2.mf_z)
	{
		m_zBuffer[p_x][p_y] = Point2.mf_z;
		p_texture->SetPixelColor(p_x, p_y, p_triangle.m_v2.m_color);
	}
	else if (m_zBuffer[p_x][p_y] < Point3.mf_z)
	{
		m_zBuffer[p_x][p_y] = Point3.mf_z;
		p_texture->SetPixelColor(p_x, p_y, p_triangle.m_v3.m_color);
	}
}

void Rasterizer::ClearZBuffer() 
{
	for (int i = 0; i < 1024; ++i)
	{
		for (int j = 0; j < 768; ++j)
		{
			m_zBuffer[i][j] = INT_MIN;
		}
	}
}

Vec3 Rasterizer::GetPixelPos(Vec4& p_v)
{
	float offsetX = (1024.0f / 2.0f);
	float offsetY = (768.0f / 2.0f);

	float scaleX = (1.0f / (offsetX / 2.0f));
	float scaleY = (1.0f / (offsetY / 2.0f));

	float x = (p_v.mf_x / scaleY) + offsetX;
	float y = (p_v.mf_y / scaleY) + offsetY;
	float z = p_v.mf_z;

	return Vec3(x, y, z);
}

//TODO: integrate zBuffer into FilltRIANGLES
void Rasterizer::FillTriangles(Vec3 & v1, Vec3 & v2, Vec3 & v3)
{
	Vec3 vm0;
	Vec3 vm1;
	Vec3 vm2;
	Vec3 point;
	Triangle tmpTriangle;

	tmpTriangle.m_v1.m_position.mf_x = v1.mf_x;
	tmpTriangle.m_v1.m_position.mf_y = v1.mf_y;
	tmpTriangle.m_v1.m_position.mf_z = v1.mf_z;
	tmpTriangle.m_v1.m_color = { 0, 255, 0, 255 };
	
	tmpTriangle.m_v2.m_position.mf_x = v2.mf_x;
	tmpTriangle.m_v2.m_position.mf_y = v2.mf_y;
	tmpTriangle.m_v2.m_position.mf_z = v2.mf_z;
	tmpTriangle.m_v3.m_color = { 0, 0, 255, 255 };
	
	tmpTriangle.m_v3.m_position.mf_x = v3.mf_x;
	tmpTriangle.m_v3.m_position.mf_y = v3.mf_y;
	tmpTriangle.m_v3.m_position.mf_z = v3.mf_z;
	tmpTriangle.m_v3.m_color = { 255, 0, 0, 255 };

	int maxY;
	int minX;
	int maxX;

	point.mf_y = std::min(v1.mf_y, std::min(v2.mf_y, v3.mf_y));
	minX = std::min(v1.mf_x, std::min(v2.mf_x, v3.mf_x));
	maxX = std::max(v1.mf_x, std::max(v2.mf_x, v3.mf_x));
	maxY = std::max(v1.mf_y, std::max(v2.mf_y, v3.mf_y));

	if (point.mf_y == v1.mf_y)
		point.mf_x = v1.mf_x;
	if (point.mf_y == v2.mf_y)
		point.mf_x = v2.mf_x;
	if (point.mf_y == v3.mf_y)
		point.mf_x = v3.mf_x;

	vm0.mf_x = v3.mf_x - v1.mf_x;
	vm0.mf_y = v3.mf_y - v1.mf_y;

	vm1.mf_x = v2.mf_x - v1.mf_x;
	vm1.mf_y = v2.mf_y - v1.mf_y;

	for (int y = point.mf_y; y < maxY; ++y)
	{
		for (int x = minX; x < maxX; ++x)
		{
			point.mf_x = x;
			point.mf_y = y;
			vm2.mf_x = point.mf_x - v1.mf_x;
			vm2.mf_y = point.mf_y - v1.mf_y;

			float dot00 = Vec3::dotProduct(vm0, vm0);
			float dot01 = Vec3::dotProduct(vm0, vm1);
			float dot02 = Vec3::dotProduct(vm0, vm2);
			float dot11 = Vec3::dotProduct(vm1, vm1);
			float dot12 = Vec3::dotProduct(vm1, vm2);

			float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
			float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
			float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

			if (u >= 0 && v >= 0 && u + v < 1)
			{
				ZBuffer(x, y, tmpTriangle, m_texture);
				SDL_SetRenderDrawColor(p_renderer, tmpTriangle.m_v1.m_color.ucm_r, tmpTriangle.m_v1.m_color.ucm_g, tmpTriangle.m_v1.m_color.ucm_b, tmpTriangle.m_v1.m_color.ucm_a);
				SDL_RenderDrawPoint(p_renderer, x, y);
			}
		}
	}


}
