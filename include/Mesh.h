#pragma once
#include <vector>
#include <Vertex.h>
#include <Triangle.h>
#include <Mesh.h>

class Mesh
{
private:
	std::vector<Vertex> m_vertices;
	std::vector<Triangle> m_triangles;

public:
	static Mesh* CreateCube();
	static Mesh* CreateSphere(int pi_latitudeCount, int pi_longitudeCount);
	static Mesh * CreateTriangle(int x, int y, int z);
	void Normalize();
	std::vector<Triangle> getTriangles();
	std::vector<Vertex> getVertices();
	void makeTriangles();
	void sort();
};
