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

		Vec4(const Vec3& p_vec3 = Vec3(), float pf_w = 1.0f);
		~Vec4() = default;
		Vec4(const Vec4& p_other);

		void Homogenize();
		float GetMagnitude() const;
		void Normalize();
		static Vec4 CrossProduct(const Vec4& p_v1, const Vec4& p_v2);

		Vec4 operator+(const Vec4& p_v1);
		Vec4 operator*(const float pf_mult);

		static float max(float p_f1, float p_f2);
		static float min(float p_f1, float p_f2);
	};

}
