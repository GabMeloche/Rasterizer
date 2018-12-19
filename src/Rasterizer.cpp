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
			Translation = Mat4::CreateTranslationMatrix({ static_cast<float>(i), 0.0f, static_cast<float>(i) });

			Mat4 Rotation;
			Rotation = Mat4::CreateRotationMatrix(p, 0, 1, 1);

			Mat4 Scale;
			Scale = Mat4::CreateScaleMatrix(0.8f);

			Mat4 TransformMat;
			TransformMat = Translation * Rotation * Scale;


			//LOOP FOR EACH LINE OF THE TRIANGLE
				float distance = 10;
				finalZ = 1.0f / (distance - currTriangle[0].m_pos->mf_z);

				float OrthoMatrix[4][4] = {
				{ 1,0.0f,0.0f,0.0f },
				{ 0.0f,1,0.0f,0.0f },
				{ 0.0f,0.0f,finalZ,0.0f },
				{ 0.0f,0.0f,0.0f,1.0f}
				};
				Ortho.SetMatrix(OrthoMatrix);

				Vec4 tmpPos1 = *currTriangle[0].m_pos;
				tmpPos1 = TransformMat * tmpPos1;
				tmpPos1 = Ortho * tmpPos1;
				//Vec3 tmpPosVec3{ tmpPos1.mf_x, tmpPos1.mf_y, tmpPos1.mf_z };
				//currTriangle[0].m_normal = currTriangle[0].m_normal * tmpPosVec3;

				Vec4 tmpPos2 = *currTriangle[1].m_pos;
				tmpPos2 = TransformMat * tmpPos2;
				tmpPos2 = Ortho * tmpPos2;
				//tmpPosVec3 = { tmpPos2.mf_x, tmpPos2.mf_y, tmpPos2.mf_z };
				//currTriangle[1].m_normal = currTriangle[1].m_normal * tmpPosVec3;

				Vec4 tmpPos3 = *currTriangle[2].m_pos;
				float tmpZ = tmpPos1.mf_z;
				tmpPos3 = TransformMat * tmpPos3;
				tmpPos3 = Ortho * tmpPos3;
				//tmpPosVec3 = { tmpPos3.mf_x, tmpPos3.mf_y, tmpPos3.mf_z };
				//currTriangle[2].m_normal = currTriangle[2].m_normal * tmpPosVec3;


				Vec3 newVecPos1 = GetPixelPos(tmpPos1);
				newVecPos1.mf_z = tmpPos1.mf_z;
				Vec3 newVecPos2 = GetPixelPos(tmpPos2);
				newVecPos2.mf_z = tmpPos2.mf_z;
				Vec3 newVecPos3 = GetPixelPos(tmpPos3);
				newVecPos3.mf_z = tmpPos3.mf_z;

				x1 = newVecPos1.mf_x;
				y1 = newVecPos1.mf_y;

				x2 = newVecPos2.mf_x;
				y2 = newVecPos2.mf_y;

				x3 = newVecPos3.mf_x;
				y3 = newVecPos3.mf_y;

				Vec3 v1 = newVecPos1;
				Vec3 v2 = newVecPos2;
				Vec3 v3 = newVecPos3;

				FillTriangles(v1, v2, v3, tmpZ, currTriangle.m_color, currTriangle);
		}
	}
}

bool Rasterizer::ZBuffer(unsigned int p_x, unsigned int p_y, float p_z)
{

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

void Rasterizer::FillTriangles(Vec3 & v1, Vec3 & v2, Vec3 & v3, float p_z, Color& p_color, Triangle& p_triangle)
{
	Vec3 vm0;
	Vec3 vm1;
	Vec3 vm2;
	Vec3 point;

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
				if (ZBuffer(x, y, p_z))
				{
					//CalculateLight(x, y, m_scene->getLights()[0], p_triangle);
					m_texture->SetPixelColor(x, y, p_color);
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

//TODO: migrate CalculateLight from Rasterizer to Light.cpp; calculations should be done based upon m_texture
void Rasterizer::CalculateLight(unsigned int p_x, unsigned int p_y, Light& p_light, Triangle& p_triangle)
{
	//AMBIENT
	Vec3 ambient = p_light.getAmbient(); //light is white
	float x = ambient.mf_x * p_triangle.m_color.ucm_r;
	float y = ambient.mf_y * p_triangle.m_color.ucm_g;
	float z = ambient.mf_z * p_triangle.m_color.ucm_b;
	Vec3 result = {x, y, z};

	//DIFFUSE
	Vec3 lightDir = p_light.getPosition() - p_triangle.m_v1.m_position;
	//lightDir.Normalize();
	float diff = std::max(Vec3::dotProduct(lightDir, p_triangle.m_v2.m_normal), 0.0f);
	Vec3 diffuse = Vec3{ 255, 255, 255 } * diff;
	result = (ambient + diffuse) * result;

	Color resultColor = { result.mf_x, result.mf_y, result.mf_z, 255 };
	m_texture->SetPixelColor(p_x, p_y, resultColor);
}
