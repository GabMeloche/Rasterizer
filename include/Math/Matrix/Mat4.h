#pragma once

#include <Math/Vector/Vec4.h>
#include <Math/Vector/Vec3.h>

namespace Math::Matrix
{
    class Mat4
    {
    public:
        float mf_Matrice4[4][4];

		Mat4();
		~Mat4() = default;
		Mat4(Mat4& p_Matrix);
		Mat4(Math::Vector::Vec3& p_vec);

		void SetMatrix(float p_Matrix[][4]);

		Mat4& operator*(const Mat4& p_Matrix);
		Vector::Vec4& operator*(const Math::Vector::Vec4& p_Vector);

		static Mat4 CreateTransformMatrix(const Vector::Vec3& rotation, const Vector::Vec3& position, const Vector::Vec3& scale);

    	static Mat4* CreateTranslationMatrix(const Vector::Vec3& p_Translation);
		static Mat4 CreateScaleMatrix(const float& p_Scale);
		static Mat4 CreateRotationMatrix(const float& p_Angle, bool& isX, bool& isY, bool& isZ);

		Vector::Vec4 Vec2dOrtho(const Mat4& p_TransformMat, const Vector::Vec4& p_Vec3D);
    };
}
