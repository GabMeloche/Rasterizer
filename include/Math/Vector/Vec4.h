#pragma once
#include <Math/Vector/Vec3.h>

namespace Math::Vector
{
	class Vec4
	{
	public:
		float mf_x;
		float mf_y;
		float mf_z;
		float mf_w;

		Vec4(const Vec3& p_vec3, float pf_w = 1.0f);
		~Vec4() = default;
		Vec4(const Vec4& p_other);

		void Homogenize();
		float GetMagnitude() const;
		void Normalize();
		Vec4& operator+(const Vec4& p_v1);
		//void operator*(const float pf_mult);
		Vec4& operator*(const float pf_mult);
	};
}
