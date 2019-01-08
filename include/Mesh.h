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
	static Mesh* CreateCube(const float p_Size);
	static Mesh* CreateSphere(const float p_Size, const int precision = 3);

	static Vertex GetMiddlePoint(Vertex& v1, Vertex& v2);
	void CreateNormals();

	std::vector<Triangle>& getTriangles();
	std::vector<Vertex>& getVertices();
	void sort();
};
