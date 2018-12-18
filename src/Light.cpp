#include <Light.h>
#include <Math/Vector/Vec3.h>

Light::Light()
{
	m_ambient = 0.3f;
	m_diffuse = 0.4f;
	m_specular = 0.4f;
	m_position = { 0.0f, 0.0f, 2.0f };
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
