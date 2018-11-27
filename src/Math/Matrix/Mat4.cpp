#include <Math/Matrix/Mat4.h>

using namespace Math::Matrix;

Mat4& Mat4::operator*(const Mat4 & p_mat1)
{
	Mat4 m_mat3;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
			for (int k = 0; k < 4; k++)
				m_mat3.mf_Matrice4[i][j] += this->mf_Matrice4[i][k] * p_mat1.mf_Matrice4[k][j];
        }
    }

	return m_mat3;
}
