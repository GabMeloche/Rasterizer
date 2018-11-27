#include <Math/Vector/Vec3.h>


using namespace Math::Vector;

Vec3::Vec3()
{
	mf_x = 0;
	mf_y = 0;
	mf_z = 0;
}
Vec3::Vec3(const float pf_x, const float pf_y, const float pf_z)
{
	mf_x = pf_x;
	mf_y = pf_y;
	mf_z = pf_z;
}

Vec3::~Vec3()
{
}

float Vec3::GetMagnitude() const
{
	return 0.0f;
}

void Vec3::Normalize()
{
}

Vec3& Vec3::operator*(float pf_scalar)
{
	Vec3 p_tmp;

	p_tmp.mf_x = mf_x * pf_scalar;
	p_tmp.mf_x = mf_y * pf_scalar;
	p_tmp.mf_x = mf_z * pf_scalar;

	return p_tmp;

}

Vec3& Vec3::operator+(Vec3& p_other)
{
	Vec3 p_tmp;

	p_tmp.mf_x = mf_x + p_other.mf_x;
	p_tmp.mf_x = mf_y + p_other.mf_y;
	p_tmp.mf_x = mf_z + p_other.mf_z;

	return p_tmp;
}
