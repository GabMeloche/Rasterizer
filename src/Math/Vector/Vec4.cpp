#include <Math\Vector\Vec4.h>
#include <cmath>

using namespace Math;

Vec4::Vec4(const Vec3& vec3, float p_w = 1.0f)
{
	m_x = vec3.x;
	m_y = vec3.y;
	m_z = vec3.z;
}
void Math::Vec4::Homogenize()
{
	if (m_w == 0)
		return;

	m_x /= m_w;
	m_y /= m_w;
	m_z /= m_w;
}

float Vec4::GetMagnitude() const
{
	float x = m_x / m_w;
	float y = m_y / m_w;
	float z = m_z / m_w;
	return sqrt(pow(x, 2)+ pow(y, 2) + pow(z, 2));
}

void Vec4::Normalize()
{
	float magn = GetMagnitude();
	m_x /= magn;
	m_y /= magn;
	m_z /= magn;
}

Vec4& Vec4::operator+(const Vec4 & p_Vec)
{
	
}

Vec4& Vec4::operator*(const float p_mult)
{
	// TODO: insert return statement here
}
