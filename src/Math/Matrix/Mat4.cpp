#include <Math/Matrix/Mat4.h>

using namespace Math::Matrix;

Mat4::Mat4(Mat4& p_Matrix)
{
    for (int i = 0; i < 4; i++)
    {
		for (int j = 0; j < 4; j++)
			mf_Matrice4[i][j] = p_Matrix.mf_Matrice4[i][j];
    }
}


Mat4& Mat4::operator*(const Mat4 & p_mat)
{
	Mat4 m_mat3;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
			for (int k = 0; k < 4; k++)
				m_mat3.mf_Matrice4[i][j] += this->mf_Matrice4[i][k] * p_mat.mf_Matrice4[k][j];
        }
    }

	return m_mat3;
}

Mat4& Mat4::operator*(const Vector::Vec4& p_vec)
{
	Vector::Vec4 tmp_Vec;

    return tmp_Vec
}

