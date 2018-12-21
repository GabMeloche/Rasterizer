#include <Math/Matrix/Mat4.h>
#include <string.h>
#include <iostream>
#include <math.h>

#define M_PI 3.141592

using namespace Math::Matrix;

Mat4::Mat4()
{
   	float f_TmpMat[4][4] = {
		{1.0f, 0.0f, 0.0f, 0.0f },
		{0.0f, 1.0f, 0.0f, 0.0f },
		{0.0f, 0.0f, 1.0f, 0.0f },
		{0.0f, 0.0f, 0.0f, 1.0f }
	};

	SetMatrix(f_TmpMat);
}


Mat4::Mat4(Mat4& p_Matrix)
{
	memcpy(mf_Matrice4, &p_Matrix, sizeof(mf_Matrice4));
}

Mat4::Mat4(Math::Vector::Vec3& p_vec)
{
	float f_TmpMat[4][4] = {
	{p_vec.mf_x, 0.0f, 0.0f, 0.0f },
	{0.0f, p_vec.mf_y, 0.0f, 0.0f },
	{0.0f, 0.0f, p_vec.mf_z, 0.0f },
	{0.0f, 0.0f, 0.0f, 1.0f }
	};

	SetMatrix(f_TmpMat);
}

void Mat4::SetMatrix(float p_Matrix[][4])
{
	memcpy(mf_Matrice4, p_Matrix, sizeof(mf_Matrice4));
}

Mat4 Mat4::operator*(const Mat4 & p_Matrix)
{
	Mat4 TmpMat;

	int i, j, k;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			TmpMat.mf_Matrice4[i][j] = 0;
			for (k = 0; k < 4; k++)
				TmpMat.mf_Matrice4[i][j] += this->mf_Matrice4[i][k] * p_Matrix.mf_Matrice4[k][j];
		}
	}

	return TmpMat;
}

Math::Vector::Vec4& Mat4::operator*(const Math::Vector::Vec4& p_Vector)
{
	Vector::Vec4 TmpVec;

	TmpVec.mf_x += this->mf_Matrice4[0][0] * p_Vector.mf_x;
	TmpVec.mf_x += this->mf_Matrice4[0][1] * p_Vector.mf_y;
	TmpVec.mf_x += this->mf_Matrice4[0][2] * p_Vector.mf_z;
	TmpVec.mf_x += this->mf_Matrice4[0][3] * p_Vector.mf_w;
    
	TmpVec.mf_y += this->mf_Matrice4[1][0] * p_Vector.mf_x;
	TmpVec.mf_y += this->mf_Matrice4[1][1] * p_Vector.mf_y;
	TmpVec.mf_y += this->mf_Matrice4[1][2] * p_Vector.mf_z;
	TmpVec.mf_y += this->mf_Matrice4[1][3] * p_Vector.mf_w;
    
	TmpVec.mf_z += this->mf_Matrice4[2][0] * p_Vector.mf_x;
	TmpVec.mf_z += this->mf_Matrice4[2][1] * p_Vector.mf_y;
	TmpVec.mf_z += this->mf_Matrice4[2][2] * p_Vector.mf_z;
	TmpVec.mf_z += this->mf_Matrice4[2][3] * p_Vector.mf_w;
    
	TmpVec.mf_w += this->mf_Matrice4[3][0] * p_Vector.mf_x;
	TmpVec.mf_w += this->mf_Matrice4[3][1] * p_Vector.mf_y;
	TmpVec.mf_w += this->mf_Matrice4[3][2] * p_Vector.mf_z;
	TmpVec.mf_w += this->mf_Matrice4[3][3] * p_Vector.mf_w;
    
    return TmpVec;
}

Mat4 Math::Matrix::Mat4::CreateTranslationMatrix(const Vector::Vec3 & p_Translation)
{
	Mat4 TranslateMat;

	float X[4][4]{
		{ 1.0f, 0.0f, 0.0f, p_Translation.mf_x },
		{ 0.0f, 1.0f, 0.0f, p_Translation.mf_y },
		{ 0.0f, 0.0f, 1.0f, p_Translation.mf_z },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};

	TranslateMat.SetMatrix(X);

	return TranslateMat;
}

Mat4 Math::Matrix::Mat4::CreateScaleMatrix(const float& p_Scale)
{
	Mat4 ScaleMat;

	float X[4][4]{
		{ p_Scale, 0.0f, 0.0f, 0.0f },
		{ 0.0f, p_Scale, 0.0f, 0.0f },
		{ 0.0f, 0.0f, p_Scale, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};

	ScaleMat.SetMatrix(X);

	return ScaleMat;
}

Mat4 Math::Matrix::Mat4::CreateRotationMatrix(const float& p_Angle, const bool& isX, const bool& isY, const bool& isZ)
{
	Mat4 RotateMatX;
	Mat4 RotateMatY;
	Mat4 RotateMatZ;

	if (isX)
	{
		float X[4][4]{
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, cos(p_Angle* M_PI / 180.0f), sin(p_Angle* M_PI / 180.0f), 0.0f },
		{ 0.0f, -sin(p_Angle* M_PI / 180.0f), cos(p_Angle* M_PI / 180.0f), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		RotateMatX.SetMatrix(X);
	}

	if (isY)
	{
		float Y[4][4]{
		{ cos(p_Angle* M_PI / 180.0f), 0.0f, -sin(p_Angle* M_PI / 180.0f), 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ sin(p_Angle* M_PI / 180.0f), 0.0f, cos(p_Angle* M_PI / 180.0f), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		RotateMatY.SetMatrix(Y);

	}

	if (isZ)
	{
		float Z[4][4]{
		{ cos(p_Angle* M_PI / 180.0f), sin(p_Angle* M_PI / 180.0f), 0.0f, 0.0f },
		{ -sin(p_Angle* M_PI / 180.0f), cos(p_Angle* M_PI / 180.0f), 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
		RotateMatZ.SetMatrix(Z);

	}

	Mat4 FinalRotateMat;
	FinalRotateMat = RotateMatY * RotateMatX * RotateMatZ;

	return FinalRotateMat;
}

Mat4 Math::Matrix::Mat4::Vec2dOrtho(const Vector::Vec4 & p_Vec3D)
{
	Mat4 Ortho;

	float distance = 2;
	float finalZ = 1 / (distance - p_Vec3D.mf_z);

	float OrthoMatrix[4][4] = {
	{ 1,0,0,0 },
	{ 0,1,0,0 },
	{ 0,0, finalZ,0 },
	{ 0,0,0,1 }
	};

	Ortho.SetMatrix(OrthoMatrix);
	return Ortho;


}

