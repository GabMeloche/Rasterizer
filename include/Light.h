#pragma once
#include <Math/Vector/Vec3.h>
#include <Texture.h>
#include <Triangle.h>

using namespace Math::Vector;

class Light
{
private:
	Vec3 m_position;
	float m_ambient;
	float m_diffuse;
	float m_specular;
public:
	Light();
	~Light() = default;
	Light(const Light& p_other);

	void setPosition(Vec3& p_position);
	void setAmbient(float p_ambient);
	void setDiffuse(float p_diffuse);
	void setSpecular(float p_specular);

	Vec3& getPosition();
	float getAmbient();
	float getDiffuse();
	float getSpecular();
	void CalculateLight(const unsigned int p_x, const unsigned int p_y, Texture* p_texture, Triangle& p_triangle, float p_z);
};
