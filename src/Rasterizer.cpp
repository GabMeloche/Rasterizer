#include <Rasterizer.h>
#include <Vertex.h>
#include <Triangle.h>
#include <Math/Vector/Vec3.h>
#include <iostream>
#include <algorithm>


Mat4 Ortho;
float pAngle = 0;
float ggg = 0;

Rasterizer::Rasterizer()
{

	m_zBuffer = new float*[1024];

	for (size_t i = 0; i < 1024; ++i)
	{
		m_zBuffer[i] = new float[768];

		for (size_t j = 0; j < 768; ++j)
		{
			m_zBuffer[i][j] = INT_MIN;
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

void Rasterizer::setScene(Scene * p_scene)
{
	m_scene = p_scene;
}

void Rasterizer::Convert2Dto3D(Vertex& m_inPoint)
{
	std::cout << m_inPoint.m_position.mf_x << '\n';
	m_inPoint.m_position.mf_x = ((m_inPoint.m_position.mf_x / 5.0f) + 1.0f) * 0.5f * 1024.0f;
	m_inPoint.m_position.mf_y = 768.0f - ((m_inPoint.m_position.mf_y / 5.0f) + 1.0f) * 0.5f * 768.0f;
	std::cout << m_inPoint.m_position.mf_x << '\n';
}

void Rasterizer::RenderScene(Scene* p_scene, Texture& p_Target)
{
	//calculate rotation angle
	if (pAngle < 360.0f)
		pAngle += 2.0f;
	else
		pAngle = 2.0f;

	ggg += 1;

	std::vector<Entity*>& allEntities = p_scene->getEntities();
	size_t eSize = allEntities.size();
	
	ClearZBuffer();
	//FOR EACH MESH
	for (size_t i = 0; i < eSize; i++)
	{
		//Calculate Transformation Matrix
		Mat4 Translation;
		Translation = Mat4::CreateTranslationMatrix({ cos(ggg / 10), 0.0f, 0.0f });

		Mat4 Rotation;
		Rotation = Mat4::CreateRotationMatrix(pAngle, 1, 1, 1);

		Mat4 Scale;
		Scale = Mat4::CreateScaleMatrix(0.8f);

		Mat4 TransformMat;
		TransformMat = Translation * Rotation * Scale;

		//find projection matrix using the first triangle
		Mat4 Proj;
		Proj = Mat4::Vec2dOrtho(*p_scene->getEntities()[i]->getMesh()->getTriangles()[0][0].m_pos, 2);

		size_t tSize = allEntities[i]->getMesh()->getTriangles().size();
		//FOR EACH TRIANGLE IN THE MESH
		for (size_t k = 0; k < tSize; ++k)
		{
			//Get Current triangle
			int m_width = p_Target.mui_w;
			Triangle& currTriangle = p_scene->getEntities()[i]->getMesh()->getTriangles()[k];


			//LOOP FOR EACH LINE OF THE TRIANGLE
			Vec4 tmpPos1 = *currTriangle[0].m_pos;
			tmpPos1 = TransformMat * tmpPos1;
			tmpPos1 = Proj * tmpPos1;

			Vec4 tmpPos2 = *currTriangle[1].m_pos;
			tmpPos2 = TransformMat * tmpPos2;
			tmpPos2 = Proj * tmpPos2;

			Vec4 tmpPos3 = *currTriangle[2].m_pos;
			tmpPos3 = TransformMat * tmpPos3;
			tmpPos3 = Proj * tmpPos3;


			Vec3 v1 = PixelPosRatio(tmpPos1);
			Vec3 v2 = PixelPosRatio(tmpPos2);
			Vec3 v3 = PixelPosRatio(tmpPos3);

			FillTriangles(v1, v2, v3, currTriangle.m_color, currTriangle);
		}
	}
}

bool Rasterizer::ZBuffer(unsigned int p_x, unsigned int p_y, float p_z)
{
	if (p_x >= m_texture->mui_w || p_y >= m_texture->mui_h || p_x <= 0 || p_y <= 0)
		return false;

	if (m_zBuffer[p_x][p_y] < p_z)
	{
		m_zBuffer[p_x][p_y] = p_z;
		return true;
	}
	else
		return false;
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

Vec3 Rasterizer::PixelPosRatio(Vec4& p_v)
{
	float offsetX = (1024.0f / 2.0f);
	float offsetY = (768.0f / 2.0f);

	float scaleY = (1.0f / (offsetY / 2.0f));

	float x = (p_v.mf_x / scaleY) + offsetX;
	float y = -(p_v.mf_y / scaleY) + offsetY;
	float z = p_v.mf_z;

	return Vec3(x, y, z);
}

void Rasterizer::FillTriangles(Vec3 & v1, Vec3 & v2, Vec3 & v3, Color& p_color, Triangle& p_triangle)
{
	Vec3 vm0;
	Vec3 vm1;
	Vec3 vm2;
	Vec3 point;

	Vec3 e1 = v2 - v1;
	Vec3 e2 = v3 - v1;

	Vec3 cross = Vec3::crossProduct(e1, e2);
	cross.Normalize();
	p_triangle.m_normal = cross;

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

	//calculate dot product of 3/5 points
	float dot00 = Vec3::dotProduct(vm0, vm0);
	float dot01 = Vec3::dotProduct(vm0, vm1);
	float dot11 = Vec3::dotProduct(vm1, vm1);


	for (int y = point.mf_y; y < maxY; ++y)
	{
		for (int x = minX; x < maxX; ++x)
		{
			point.mf_x = x;
			point.mf_y = y;
			vm2.mf_x = point.mf_x - v1.mf_x;
			vm2.mf_y = point.mf_y - v1.mf_y;

			//calculate dot products of the 2 other points
			float dot02 = Vec3::dotProduct(vm0, vm2);
			float dot12 = Vec3::dotProduct(vm1, vm2);

			float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
			float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
			float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

			if (u >= 0.0f && v >= 0.0f && u + v < 1.0f )
			{
				float tmpZ = v2.mf_z * v + v3.mf_z * u + (v1.mf_z * ((1.0f - v) + (1.0f - u)));

				if (ZBuffer(x, y, tmpZ))
				{
					m_texture->SetPixelColor(x, y, p_color);
					for (auto& light : m_scene->getLights())
					{
						light.CalculateLight(x, y, m_texture, p_triangle, tmpZ);
					}
					Color* tmpColor = &m_texture->GetPixelColor(x, y);
					SDL_SetRenderDrawColor(p_renderer, 
						tmpColor->ucm_r, 
						tmpColor->ucm_g, 
						tmpColor->ucm_b, 
						tmpColor->ucm_a);
					SDL_RenderDrawPoint(p_renderer, x, y);
				}
			}
		}
	}
}
