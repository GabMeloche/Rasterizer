#pragma once
#include <cassert>

namespace Math::Vector
{
	class Vec3
	{

	public:
		Vec3();
		Vec3(const float pf_x, const float pf_y, const float pf_z);
		Vec3(const float pf_xyz);

		~Vec3();

		float mf_x;
		float mf_y;
		float mf_z;

		float GetMagnitude() const;
		static float DistanceBtwPts(const Vec3& p_v1, const Vec3& p_v2);
		static float dotProduct(Vec3& p_v1, Vec3& p_v2);
		static Vec3 crossProduct(Vec3& p_v1, Vec3& p_v2);
		void Normalize();
		static float Angle(Vec3& p_v1, Vec3& p_v2);

		Vec3 operator*(float pf_scalar);
		Vec3 operator*(Vec3& p_other);
		Vec3 operator+=(Vec3& p_v);
		float operator[](int p_index);
		static void SortVertices(Vec3& p_vec1, Vec3& p_vec2, Vec3& p_vec3);
	};

	Vec3 operator+(Vec3& p_1, Vec3& p_2);
	Vec3 operator-(Vec3& p_1, Vec3& p_2);

}
