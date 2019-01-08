#include <Light.h>
#include <Math/Vector/Vec3.h>
#include <Texture.h>
#include <Triangle.h>
#include <algorithm>
#include <iostream>

Light::Light()
{
	m_ambient = 0.3f;
	m_diffuse = 0.6f;
	m_specular = 0.4f;
	m_position = { 1.0f, 0.0f, 0.0f };
}

Light::Light(const Light & p_other)
{
	m_position = p_other.m_position;
	m_ambient = p_other.m_ambient;
	m_diffuse = p_other.m_diffuse;
	m_specular = p_other.m_specular;
}

void Light::setPosition(Vec3& p_position)
{
	m_position = p_position;
}

void Light::setAmbient(float p_ambient)
{
	m_ambient = p_ambient;
}

void Light::setDiffuse(float p_diffuse)
{
	m_diffuse = p_diffuse;
}

void Light::setSpecular(float p_specular)
{
	m_specular = p_specular;
}

Vec3& Light::getPosition()
{
	return m_position;
}

float Light::getAmbient()
{
	return m_ambient;
}

float Light::getDiffuse()
{
	return m_diffuse;
}

float Light::getSpecular()
{
	return m_specular;
}

//NaN problem is with p_triangle normals (-NaN(ind))
void Light::CalculateLight(const unsigned int p_x, const unsigned int p_y, Texture* p_texture, Triangle& p_triangle, float p_z)
{
	Color& pixelColor = p_texture->GetPixelColor(p_x, p_y);
	Vec3 lightColor = { 255.0f, 255.0f, 255.0f };
	/*Vec3 objectColor = { static_cast<float>(p_texture->GetPixelColor(p_x, p_y).ucm_r),
		static_cast<float>(p_texture->GetPixelColor(p_x, p_y).ucm_g),
		static_cast<float>(p_texture->GetPixelColor(p_x, p_y).ucm_b) };*/

	float pointX = (static_cast<float>(p_x) - (p_texture->mui_w)) / (p_texture->mui_w / 2);
	float pointY = (static_cast<float>(p_y) - (p_texture->mui_h)) / (p_texture->mui_h / 2);

	Vec3 Point = { pointX, pointY, 0.0f };
	//Point.Normalize();
	Point.mf_z = p_z;

	//AMBIENT
	Vec3 ambient = this->getAmbient(); //light is white now; if not white, then multiply ambient by light's color
	float x = ambient.mf_x * pixelColor.ucm_r;
	float y = ambient.mf_y * pixelColor.ucm_g;
	float z = ambient.mf_z * pixelColor.ucm_b;
	Vec3 result = { x, y, z };

	//DIFFUSE
	Vec3 lightDir = this->getPosition() - Point;
	//lightDir.Normalize();
	float diff = std::abs(Vec3::dotProduct(lightDir, p_triangle.m_normal));
	Vec3 diffuse = lightColor * diff;

	Vec3 test = { pixelColor.ucm_r / 255.0f, pixelColor.ucm_g / 255.0f, pixelColor.ucm_b / 255.0f };
	Vec3 temp = result + diffuse;
	Vec3 resultBis = temp * test;

	//SPECULAR
	/*Vec3 camera = { 0.0f, 0.0f, 1.0f };
	Vec3 reflectDir = p_triangle.m_v1.m_normal * (2 * (Vec3::dotProduct(lightDir, p_triangle.m_v1.m_normal)));
	Vec3 inverseLight = lightDir * -1;
	reflectDir = inverseLight - reflectDir;
	float camXreflect = Vec3::dotProduct(camera, reflectDir);
	if (camXreflect < 0)
		camXreflect *= -1;

	float spec = pow(camXreflect, 2);
	Vec3 specular = lightColor * m_specular * spec;
	//std::cout << "spec: " << spec << std::endl;
	//std::cout << "specular: " << specular.mf_x << ", " << specular.mf_y << ", " << specular.mf_z << std::endl;
	result = result + specular;*/

	//std::cout << "color specular: " << result.mf_x << ", " << result.mf_y << std::endl;
	Color resultColor = { static_cast<unsigned char>(resultBis.mf_x), static_cast<unsigned char>(resultBis.mf_y), static_cast<unsigned char>(resultBis.mf_z), 255 };
	/*if (resultColor.ucm_r <= 10.0f)
	{
		std::cout << "ble";
	}*/
	p_texture->SetPixelColor(p_x, p_y, resultColor);
}