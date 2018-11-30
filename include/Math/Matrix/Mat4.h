#pragma once

#include <Math/Vector/Vec4.h>

namespace Math::Matrix
{
    class Mat4
    {
    public:
        float mf_Matrice4[4][4];

		Mat4();
		~Mat4() = default;
		Mat4(Mat4& p_Matrix);

		void SetMatrix(float p_Matrix[][4]);

		Mat4& operator*(const Mat4& p_Matrix);
		Vector::Vec4& operator*(const Math::Vector::Vec4& p_Vector);

		static Mat4 CreateTransformMatrix(const Vector::Vec3& rotation, const Vector::Vec3& position, const Vector::Vec3& scale);

    	static Mat4 CreateTranslationMatrix(const Vector::Vec3& p_Translation);
		static Mat4 CreateScaleMatrix(const Vector::Vec3& p_Scale);
		static Mat4 CreateRotationMatrix(const Vector::Vec3& p_Rotation);
    };
}
