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

Math::Vector::Vec4& Mat4::operator*(const Math::Vector::Vec4& p_vec)
{
	Vector::Vec4 tmp_Vec;

	for (int i = 0; i < 4; i++)
	{
		tmp_Vec.mf_x += this->mf_Matrice4[0][i] * p_vec.mf_x;
	}
	for (int i = 0; i < 4; i++)
	{
		tmp_Vec.mf_y += this->mf_Matrice4[1][i] * p_vec.mf_y;
	}
    for (int i = 0; i < 4; i++)
	{
		tmp_Vec.mf_z += this->mf_Matrice4[2][i] * p_vec.mf_z;
	}
    for (int i = 0; i < 4; i++)
	{
		tmp_Vec.mf_w += this->mf_Matrice4[3][i] * p_vec.mf_w;
	}

    return tmp_Vec;
}

