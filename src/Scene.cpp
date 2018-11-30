#include <Scene.h>
#include <Entity.h>
#include <vector>

Scene::~Scene()
{
	for (size_t i = 0; i < m_entities.size(); ++i)
	{
		m_entities[i].~Entity();
	}
}

Scene::Scene(const Scene & p_other)
{
	m_entities = p_other.m_entities;
}
