#include <Math/Matrix/Mat4.h>
#include <string.h>
#include <iostream>

using namespace Math::Matrix;

Mat4::Mat4()
{
   	float f_TmpMat[4][4] = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};

	SetMatrix(f_TmpMat);
}


Mat4::Mat4(Mat4& p_Matrix)
{
	memcpy(mf_Matrice4, &p_Matrix, sizeof(mf_Matrice4));
}

void Mat4::SetMatrix(float p_Matrix[][4])
{
	memcpy(mf_Matrice4, p_Matrix, sizeof(mf_Matrice4));
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

Mat4 Math::Matrix::Mat4::CreateTranslationMatrix(const Vector::Vec3 & translation)
{
	Mat4 TmpMat;

	TmpMat.mf_Matrice4[0][3] = translation.mf_x;
	TmpMat.mf_Matrice4[1][3] = translation.mf_y;
	TmpMat.mf_Matrice4[2][3] = translation.mf_z;

	return TmpMat;
}

