#include "..\include\Entity.h"

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