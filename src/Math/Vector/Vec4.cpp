#include <Math/Vector/Vec4.h>
#include <Math/Vector/Vec3.h>
#include <cmath>

using namespace Math::Vector;

Vec4::Vec4(const Vec3& p_vec3, float pf_w)
{
	mf_x = p_vec3.mf_x;
	mf_y = p_vec3.mf_y;
	mf_z = p_vec3.mf_z;
	mf_w = pf_w;
}

Vec4::Vec4(const Vec4& p_other)
{
	mf_x = p_other.mf_x;
	mf_y = p_other.mf_y;
	mf_z = p_other.mf_z;
	mf_w = p_other.mf_w;
}

void Vec4::Homogenize()
{
	if (mf_w == 0.0f)
		return;

	mf_x /= mf_w;
	mf_y /= mf_w;
	mf_z /= mf_w;
}

float Vec4::GetMagnitude() const
{
	if (mf_w == 0.0f)
		return 0.0f;

	float x = mf_x / mf_w;
	float y = mf_y / mf_w;
	float z = mf_z / mf_w;
	return sqrt(pow(x, 2.0f)+ pow(y, 2.0f) + pow(z, 2.0f));
}

void Vec4::Normalize()
{
	float magn = GetMagnitude();

	if (magn == 0.0f)
		return;

	mf_x /= magn;
	mf_y /= magn;
	mf_z /= magn;
}

Vec4 Math::Vector::Vec4::CrossProduct(const Vec4 & p_v1, const Vec4 & p_v2)
{
	float x = (p_v1.mf_y * p_v2.mf_z) - (p_v1.mf_z * p_v2.mf_y);
	float y = -((p_v1.mf_x * p_v2.mf_z) - (p_v1.mf_z * p_v2.mf_x));
	float z = (p_v1.mf_x * p_v2.mf_y) - (p_v1.mf_y * p_v2.mf_x);
	float w = 1.0f;

	return Vec4(Vec3(x, y, z), w);
}

Vec4 Vec4::operator+(const Vec4& p_v)
{
	return (Vec3(p_v.mf_x + mf_x,
		p_v.mf_y + mf_y,
		p_v.mf_z + mf_z));
}

Vec4 Vec4::operator*(const float pf_mult)
{
	float x = mf_x * pf_mult;
	float y = mf_y * pf_mult;
	float z = mf_z * pf_mult;
	float w = mf_w * pf_mult;
	return Vec4(Vec3(x, y, z), w);
}

float Math::Vector::Vec4::max(float p_f1, float p_f2)
{
	if (p_f1 > p_f2)
		return p_f1;
	else
		return p_f2;
}

float Math::Vector::Vec4::min(float p_f1, float p_f2)
{
	if (p_f1 < p_f2)
		return p_f1;
	else
		return p_f2;
}
