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

Mat4& Mat4::operator*(const Mat4 & p_Matrix)
{
	auto* TmpMat = new Mat4;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
			for (int k = 0; k < 4; k++)
				TmpMat->mf_Matrice4[i][j] += this->mf_Matrice4[i][k] * p_Matrix.mf_Matrice4[k][j];
        }
    }

	return *TmpMat;
}

Math::Vector::Vec4& Mat4::operator*(const Math::Vector::Vec4& p_Vector)
{
	auto* TmpVec = new Vector::Vec4;

	TmpVec->mf_x += this->mf_Matrice4[0][0] * p_Vector.mf_x;
	TmpVec->mf_x += this->mf_Matrice4[0][1] * p_Vector.mf_y;
	TmpVec->mf_x += this->mf_Matrice4[0][2] * p_Vector.mf_z;
	TmpVec->mf_x += this->mf_Matrice4[0][3] * p_Vector.mf_w;
    
	TmpVec->mf_y += this->mf_Matrice4[1][0] * p_Vector.mf_x;
	TmpVec->mf_y += this->mf_Matrice4[1][1] * p_Vector.mf_y;
	TmpVec->mf_y += this->mf_Matrice4[1][2] * p_Vector.mf_z;
	TmpVec->mf_y += this->mf_Matrice4[1][3] * p_Vector.mf_w;
    
	TmpVec->mf_z += this->mf_Matrice4[2][0] * p_Vector.mf_x;
	TmpVec->mf_z += this->mf_Matrice4[2][1] * p_Vector.mf_y;
	TmpVec->mf_z += this->mf_Matrice4[2][2] * p_Vector.mf_z;
	TmpVec->mf_z += this->mf_Matrice4[2][3] * p_Vector.mf_w;
    
	TmpVec->mf_w += this->mf_Matrice4[3][0] * p_Vector.mf_x;
	TmpVec->mf_w += this->mf_Matrice4[3][1] * p_Vector.mf_y;
	TmpVec->mf_w += this->mf_Matrice4[3][2] * p_Vector.mf_z;
	TmpVec->mf_w += this->mf_Matrice4[3][3] * p_Vector.mf_w;
    
    return *TmpVec;
}

Mat4 Math::Matrix::Mat4::CreateTransformMatrix(const Vector::Vec3 & rotation, const Vector::Vec3 & position, const Vector::Vec3 & scale)
{
	Mat4 TmpMatTrans;
	Mat4 TmpMatScale;
	Mat4 TmpMatRotate;

	TmpMatTrans = CreateTranslationMatrix(position);
	TmpMatRotate = CreateRotationMatrix(rotation);
	TmpMatScale = CreateScaleMatrix(scale);

	Mat4 FinalMat = TmpMatTrans * TmpMatRotate * TmpMatScale;

	return FinalMat;
}

Mat4 Math::Matrix::Mat4::CreateTranslationMatrix(const Vector::Vec3 & p_Translation)
{
	Mat4 TmpMat;

	TmpMat.mf_Matrice4[0][3] = p_Translation.mf_x;
	TmpMat.mf_Matrice4[1][3] = p_Translation.mf_y;
	TmpMat.mf_Matrice4[2][3] = p_Translation.mf_z;

	return TmpMat;
}

Mat4 Math::Matrix::Mat4::CreateScaleMatrix(const Vector::Vec3 & p_Scale)
{
	Mat4 TmpMat;

	TmpMat.mf_Matrice4[0][0] = p_Scale.mf_x;
	TmpMat.mf_Matrice4[1][1] = p_Scale.mf_y;
	TmpMat.mf_Matrice4[2][2] = p_Scale.mf_z;

	return TmpMat;
}

Mat4 Math::Matrix::Mat4::CreateRotationMatrix(const Vector::Vec3 & p_Rotation)
{
	Mat4 TmpMatX;
	Mat4 TmpMatY;
	Mat4 TmpMatZ;

	TmpMatX.mf_Matrice4[1][1] = cos(p_Rotation.mf_x);
	TmpMatX.mf_Matrice4[1][2] = -sin(p_Rotation.mf_x);
	TmpMatX.mf_Matrice4[2][1] = cos(p_Rotation.mf_x);
	TmpMatX.mf_Matrice4[2][2] = sin(p_Rotation.mf_x);
    
	TmpMatY.mf_Matrice4[0][0] = cos(p_Rotation.mf_y);
	TmpMatY.mf_Matrice4[0][2] = -sin(p_Rotation.mf_y);
	TmpMatY.mf_Matrice4[2][0] = cos(p_Rotation.mf_y);
	TmpMatY.mf_Matrice4[2][2] = sin(p_Rotation.mf_y);
    
	TmpMatZ.mf_Matrice4[0][0] = cos(p_Rotation.mf_z);
	TmpMatZ.mf_Matrice4[0][1] = -sin(p_Rotation.mf_z);
	TmpMatZ.mf_Matrice4[1][0] = cos(p_Rotation.mf_z);
	TmpMatZ.mf_Matrice4[1][1] = sin(p_Rotation.mf_z);

	Mat4 TmpMatTotal = TmpMatX * TmpMatY * TmpMatZ;

	return TmpMatTotal;
}

