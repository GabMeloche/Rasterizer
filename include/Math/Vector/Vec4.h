#pragma once
#include <Math/Vector/Vec3.h>

namespace Math
{
	class Vec4
	{
	public:
		float m_x;
		float m_y;
		float m_z;
		float m_w;

		Vec4(const Vec3& vec3, float p_w = 1.0f);
		~Vec4() = default;

		void Homogenize();
		float GetMagnitude() const;
		void Normalize();
		static Vec4& operator+(const Vec4& p_Vec);
		static Vec4& operator*(const float p_mult);
	};
}
