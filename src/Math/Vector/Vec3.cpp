#include <Math/Vector/Vec3.h>
#include <Math/Vector/Vec4.h>
#include <math.h>
#include <Color.h>
#include <iostream>


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
	return sqrt(pow(mf_x, 2.0f) + pow(mf_y, 2.0f) + pow(mf_z, 2.0f));
}

float Vec3::DistanceBtwPts(const Vec3& p_v1, const Vec3& p_v2)
{
	return sqrt(pow(p_v1.mf_x - p_v2.mf_x, 2.0f) 
		+ pow(p_v1.mf_y - p_v2.mf_y, 2.0f) 
		+ pow(p_v1.mf_z - p_v2.mf_z, 2.0f));
}

float Vec3::dotProduct(Vec3 & p_v1, Vec3 & p_v2)
{
	
	return (p_v1.mf_x * p_v2.mf_x) + 
		(p_v1.mf_y * p_v2.mf_y) +
		(p_v1.mf_z * p_v2.mf_z);
}

Vec3 Vec3::crossProduct(Vec3 & p_v1, Vec3 & p_v2)
{
	Vec3 newVec;

	newVec.mf_x = (p_v1.mf_y * p_v2.mf_z) - (p_v1.mf_z * p_v2.mf_y);
	newVec.mf_y = (p_v1.mf_z * p_v2.mf_x) - (p_v1.mf_x * p_v2.mf_z);
	newVec.mf_z = (p_v1.mf_x * p_v2.mf_y) - (p_v1.mf_y * p_v2.mf_x);

	return newVec;
}

void Vec3::Normalize()
{
	if(mf_x != 0.0f)
		mf_x = mf_x / sqrt(pow(mf_x, 2.0f));
	if (mf_y != 0.0f)
		mf_y = mf_y / sqrt(pow(mf_y, 2.0f));
	if (mf_z != 0.0f)
		mf_z = mf_z / sqrt(pow(mf_z, 2.0f));

	float length = sqrt(pow(mf_x, 2.0f) + pow(mf_y, 2.0f) + pow(mf_z, 2.0f));

	mf_x = mf_x / length;
	mf_y = mf_y / length;
	mf_z = mf_z / length;
}

float Vec3::Angle(Vec3& p_v1, Vec3& p_v2)
{
	float cos = (Vec3::dotProduct(p_v1, p_v2) / (p_v1.GetMagnitude() * p_v2.GetMagnitude()));
	return cos;
}

Vec3 Vec3::operator*(float pf_scalar)
{
	float x = mf_x * pf_scalar;
	float y = mf_y * pf_scalar;
	float z = mf_z * pf_scalar;

	return Vec3(x, y, z);

}

Vec3 Math::Vector::Vec3::operator*(Vec3 & p_other)
{
	return Vec3(mf_x * p_other.mf_x,
		mf_y * p_other.mf_y,
		mf_z * p_other.mf_z);
}


float Vec3::operator[](int p_index)
{
	assert(p_index < 3);

	switch (p_index)
	{
	default:
		break;
	case 0:
		return mf_x;
	case 1:
		return mf_y;
	case 2:
		return mf_z;
	}
	return 0.0f;
}

Vec3 Math::Vector::operator+(Vec3& p_1, Vec3& p_2)
{
	float x = p_1.mf_x + p_2.mf_x;
	float y = p_1.mf_y + p_2.mf_y;
	float z = p_1.mf_z + p_2.mf_z;

	return Vec3(x, y, z);
}
Vec3 Vec3::operator+=(Vec3 & p_v)
{
	float x = mf_x + p_v.mf_x;
	float y = mf_y + p_v.mf_y;
	float z = mf_z + p_v.mf_z;

	return Vec3(x, y, z);
}
Vec3 Math::Vector::operator-(Vec3& p_1, Vec3& p_2)
{
	float x = p_1.mf_x - p_2.mf_x;
	float y = p_1.mf_y - p_2.mf_y;
	float z = p_1.mf_z - p_2.mf_z;

	return Vec3(x, y, z);
}

void Vec3::SortVertices(Vec3 & p_vec1, Vec3 & p_vec2, Vec3 & p_vec3)
{
	Vec3 tmpVec;

	if (p_vec3.mf_y < p_vec2.mf_y)
	{
		tmpVec = p_vec2;
		p_vec2 = p_vec3;
		p_vec3 = tmpVec;
	}
	if (p_vec2.mf_y < p_vec1.mf_y)
	{
		tmpVec = p_vec1;
		p_vec1 = p_vec2;
		p_vec2 = tmpVec;
	}
	if (p_vec1.mf_y < p_vec3.mf_y)
	{
		tmpVec = p_vec3;
		p_vec3 = p_vec1;
		p_vec1 = tmpVec;
	}
	if (p_vec3.mf_y < p_vec2.mf_y)
	{
		tmpVec = p_vec2;
		p_vec2 = p_vec3;
		p_vec3 = tmpVec;
	}
}
