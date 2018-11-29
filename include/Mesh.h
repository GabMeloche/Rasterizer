#pragma once
#include <vector>
#include <Vertex.h>

class Mesh
{
private:
	std::vector<Vertex> m_vertices;
	std::vector<int> m_indices;

public:
	static Mesh* CreateCube();
	static Mesh* CreateSphere(int pi_latitudeCount, int pi_longitudeCount);
};
