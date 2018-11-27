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
        Mat4& operator*(const Vector::Vec4& p_vec)
	};
}
