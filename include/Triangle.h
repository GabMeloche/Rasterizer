#pragma once
#include <Vertex.h>
#include <vector>
#include <cassert>

struct Triangle
{
	Vertex m_v1;
	Vertex m_v2;
	Vertex m_v3;
	Vec3 m_normal;
	Color m_color;

	Vertex& operator[](int p_index)
	{
		switch (p_index % 3)
		{
		case 0:
			return m_v1;
		case 1:
			return m_v2;
		case 2:
			return m_v3;
		default:
			break;
		}
	}
};