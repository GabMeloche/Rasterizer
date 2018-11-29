#pragma once
#include <vector>
#include <Vertex.h>
#include <Triangle.h>

class Mesh
{
private:
	std::vector<Vertex> m_vertices;
	std::vector<Triangle> m_triangles;
	std::vector<int> m_indices;

public:
	static Mesh* CreateCube();
	static Mesh* CreateSphere(int pi_latitudeCount, int pi_longitudeCount);
};
