#pragma once
#include <Entity.h>
#include <Light.h>
#include <vector>

class Scene
{
private:
	std::vector<Entity*> m_entities;
	std::vector<Light> m_lights;
public:
	Scene() = default;
	~Scene();
	Scene(const Scene& p_other);

	std::vector<Entity*>& getEntities();
	std::vector<Light>& getLights();
};
