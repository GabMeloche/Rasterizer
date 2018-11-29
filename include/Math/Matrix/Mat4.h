#pragma once

#include <Math/Vector/Vec4.h>

namespace Math::Matrix
{
    class Mat4
    {
    public:
        float mf_Matrice4[4][4];

		Mat4() = default;
		~Mat4() = default;
		Mat4(Mat4& p_Matrix);

		Mat4& operator*(const Mat4& p_mat);
		Vector::Vec4& operator*(const Math::Vector::Vec4& p_vec);

		//static Mat4 CreateTransformMatrix(const Vector::Vec3& rotation, const Vector::Vec3& position, const Vector::Vec3& scale);
	};
}
