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
