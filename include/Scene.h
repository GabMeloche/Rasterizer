#pragma once
#include <Entity.h>
#include <vector>

class Scene
{
private:
	std::vector<Entity*> m_entities;
public:
	Scene() = default;
	~Scene();
	Scene(const Scene& p_other);

	std::vector<Entity*>& getEntities();
};
