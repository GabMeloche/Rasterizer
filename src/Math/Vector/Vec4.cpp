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
	if (mf_w == 0)
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
	return sqrt(pow(x, 2)+ pow(y, 2) + pow(z, 2));
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

Vec4& Vec4::operator+(const Vec4& p_v)
{
	Vec4* p_tmp = new Vec4(Vec3(p_v.mf_x + mf_x,
		p_v.mf_y + mf_y,
		p_v.mf_z + mf_z));
	return *p_tmp;
}

Vec4& Vec4::operator*(const float pf_mult)
{
	float x = mf_x * pf_mult;
	float y = mf_y * pf_mult;
	float z = mf_z * pf_mult;
	float w = mf_w * pf_mult;
	Vec4* p_tmp = new Vec4(Vec3(x, y, z), w);
	return *p_tmp;
}
