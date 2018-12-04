#pragma once
#include <Math/Vector/Vec3.h>

using namespace Math::Vector;

struct Vertex
{
	Vec3 m_position;

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
