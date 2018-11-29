#include <Mesh.h>
#include <Vertex.h>
#include <vector>

Mesh* Mesh::CreateCube()
{
	Mesh* mesh = new Mesh;
	for (float i = 0.0f; i < 2.0f; ++i)
	{
		mesh->m_vertices.emplace_back(Vertex{ Vec3{-0.5f, 0.5f, i} });
		mesh->m_vertices.emplace_back(Vertex{ Vec3{0.5f, 0.5f, i} });
		mesh->m_vertices.emplace_back(Vertex{ Vec3{-0.5f, -0.5f, i} });
		mesh->m_vertices.emplace_back(Vertex{ Vec3{0.5f, -0.5f, i} });
		mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[0], 
												mesh->m_vertices[1], 
												mesh->m_vertices[2] });
		mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[1],
												mesh->m_vertices[2],
												mesh->m_vertices[3] });
	}
	return mesh;
}

Mesh * Mesh::CreateSphere(int pi_latitudeCount, int pi_longitudeCount)
{
	return nullptr;
}
