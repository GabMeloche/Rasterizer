#pragma once

namespace Math::Matrix::Mat4
{
    class Mat4
    {
    public:

		float** mf_Matrice4[4][4];

		Mat4() = default;
		~Mat4() = default;

		Mat4& operator*(Mat4& p_mat1, Mat4& p_mat2);
    };
}