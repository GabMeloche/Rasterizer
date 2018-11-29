#include <Math/Matrix/Mat4.h>
#include <string.h>

using namespace Math::Matrix;

Mat4::Mat4(Mat4& p_Matrix)
{
	//float f_TmpMat[4][4] = {
	//	{1, 0, 0, 0},
	//	{0, 1, 0, 0},
	//	{0, 0, 1, 0},
	//	{0, 0, 0, 1}
	//};

	memcpy(mf_Matrice4, , sizeof(mf_Matrice4));
}


Mat4& Mat4::operator*(const Mat4 & p_mat)
{
	auto* TmpMat = new Mat4;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
			for (int k = 0; k < 4; k++)
				TmpMat->mf_Matrice4[i][j] += this->mf_Matrice4[i][k] * p_mat.mf_Matrice4[k][j];
        }
    }

	return *TmpMat;
}

Math::Vector::Vec4& Mat4::operator*(const Math::Vector::Vec4& p_vec)
{
	auto* TmpVec = new Vector::Vec4;

	for (int i = 0; i < 4; i++)
	{
		TmpVec->mf_x += this->mf_Matrice4[0][i] * p_vec.mf_x;
	}
	for (int i = 0; i < 4; i++)
	{
		TmpVec->mf_y += this->mf_Matrice4[1][i] * p_vec.mf_y;
	}
    for (int i = 0; i < 4; i++)
	{
		TmpVec->mf_z += this->mf_Matrice4[2][i] * p_vec.mf_z;
	}
    for (int i = 0; i < 4; i++)
	{
		TmpVec->mf_w += this->mf_Matrice4[3][i] * p_vec.mf_w;
	}
    
    return *TmpVec;
}

