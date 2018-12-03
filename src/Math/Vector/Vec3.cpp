#include <Math/Vector/Vec3.h>
#include <math.h>


using namespace Math::Vector;

Vec3::Vec3()
{
	mf_x = 0.0f;
	mf_y = 0.0f;
	mf_z = 0.0f;
}
Vec3::Vec3(const float pf_x, const float pf_y, const float pf_z)
{
	mf_x = pf_x;
	mf_y = pf_y;
	mf_z = pf_z;
}

Vec3::Vec3(const float pf_xyz)
{
	mf_x = pf_xyz;
	mf_y = pf_xyz;
	mf_z = pf_xyz;
}


Vec3::~Vec3()
{
}

float Vec3::GetMagnitude() const
{
	return sqrt(pow(mf_x, 2) + pow(mf_y, 2) + pow(mf_z, 2));
}

float Vec3::DistanceBtwPts(const Vec3& p_v1, const Vec3& p_v2)
{
	return sqrt(pow(p_v1.mf_x - p_v2.mf_x, 2) 
		+ pow(p_v1.mf_y - p_v2.mf_y, 2) 
		+ pow(p_v1.mf_z - p_v2.mf_z, 2));
}

void Vec3::Normalize()
{
	mf_x = mf_x / sqrt(pow(mf_x, 2));
	mf_y = mf_y / sqrt(pow(mf_y, 2));
	mf_z = mf_z / sqrt(pow(mf_z, 2));
}

Vec3& Vec3::operator*(float pf_scalar)
{
	Vec3* p_tmp = new Vec3;

	p_tmp->mf_x = mf_x * pf_scalar;
	p_tmp->mf_x = mf_y * pf_scalar;
	p_tmp->mf_x = mf_z * pf_scalar;

	return *p_tmp;

}

Vec3& Vec3::operator+(Vec3& p_other)
{
	Vec3* p_tmp = new Vec3;

	p_tmp->mf_x = mf_x + p_other.mf_x;
	p_tmp->mf_x = mf_y + p_other.mf_y;
	p_tmp->mf_x = mf_z + p_other.mf_z;

	return *p_tmp;
}
