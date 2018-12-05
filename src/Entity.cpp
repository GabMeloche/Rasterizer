#include <Entity.h>
#include <algorithm>

Entity::~Entity()
{
	if (m_mesh == nullptr)
		return;

	delete m_mesh;
}

Entity::Entity(const Entity& p_other)
{
	m_mesh = p_other.m_mesh;
	m_mat = p_other.m_mat;
}

void Entity::setMesh(Mesh* mesh)
{
	m_mesh = mesh;
}

Mesh * Entity::getMesh()
{
	return m_mesh;
}

float* Entity::CheckTriangleZone()
{
	float values[4];
	std::vector<float> xValues;
	std::vector<float> yValues;

	for (size_t i = 0; i < m_triangles.size(); ++i)
	{
		for (size_t k = 0; j < 2; ++j)
		{
			xValues.emplace_back(m_triangles[j][k].m_position.mf_x);
			yValues.emplace_back(m_triangles[j][k].m_position.mf_y);
		}
	}

	std::sort(xValues.begin(), xValues.end());
	std::sort(yValues.begin(), yValues.end());

	values[0] = xValues[0];
	values[1] = xValues[xValues.size() - 1];
	values[2] = yValues[0];
	values[3] = yValues[yValues.size() - 1];

	return values;
}
