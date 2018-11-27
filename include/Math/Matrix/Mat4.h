#pragma once

namespace Math::Matrix
{
    class Mat4
    {
    public:

        // ReSharper disable once IdentifierTypo
        float mf_Matrice4[4][4];

		Mat4() = default;
		~Mat4() = default;

		Mat4& operator*(const Mat4& p_mat1);
	};
}