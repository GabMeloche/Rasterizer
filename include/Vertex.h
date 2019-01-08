#pragma once
#include <Math/Vector/Vec3.h>
#include <Math/Matrix/Mat4.h>
#include <Color.h>

using namespace Math::Vector;
using namespace Math::Matrix;

struct Vertex
{
	Vec3 m_position;
	Vec3 m_normal;
	Vec4* m_pos;
	Mat4* m_rotation;
	Mat4* m_scale;

	Color m_color;

	bool operator<(const Vertex& p_other)
	{
		if (m_position.mf_x < p_other.m_position.mf_x)
		{
			return true;
		}
		if (m_position.mf_x == p_other.m_position.mf_x)
		{
			if (m_position.mf_y < p_other.m_position.mf_y)
				return true;
			else if (m_position.mf_z < p_other.m_position.mf_z)
				return true;
		}
		return false;
	}

};
