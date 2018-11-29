#define _USE_MATH_DEFINES
#include <Mesh.h>
#include <Vertex.h>
#include <vector>
#include <cmath>

Mesh* Mesh::CreateCube()
{
	Mesh* mesh = new Mesh;

	mesh->m_vertices.emplace_back(Vertex{ Vec3{-0.5f, 0.5f, 0.0f} });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{0.5f, 0.5f, 0.0f} });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{-0.5f, -0.5f, 0.0f} });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{0.5f, -0.5f, 0.0f} });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -0.5f, 0.5f, 1.0f } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ 0.5f, 0.5f, 1.0f } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -0.5f, -0.5f, 1.0f } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ 0.5f, -0.5f, 1.0f } });

	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[0], 
											mesh->m_vertices[1], 
											mesh->m_vertices[2] });
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[1],
											mesh->m_vertices[2],
											mesh->m_vertices[3] }); //front 

	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[0],
		mesh->m_vertices[1],
		mesh->m_vertices[4] });
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[1],
		mesh->m_vertices[4],
		mesh->m_vertices[5] }); //top

	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[0], 
		mesh->m_vertices[2],
		mesh->m_vertices[4] });
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[2],
		mesh->m_vertices[4],
		mesh->m_vertices[6] }); //left

	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[5],
		mesh->m_vertices[4],
		mesh->m_vertices[6] });
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[5],
		mesh->m_vertices[6],
		mesh->m_vertices[7] }); //back

	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[5],
		mesh->m_vertices[1],
		mesh->m_vertices[7] });
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[1],
		mesh->m_vertices[7],
		mesh->m_vertices[3] }); //right

	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[3],
		mesh->m_vertices[2],
		mesh->m_vertices[7] });
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[2],
		mesh->m_vertices[7],
		mesh->m_vertices[6] }); //bottom

	return mesh;
}

Mesh * Mesh::CreateSphere(int pi_latitudeCount, int pi_longitudeCount)
{
	Mesh* mesh = new Mesh;

	for (int i = 0; i < pi_latitudeCount; ++i)
	{
		for (int j = 0; j < pi_longitudeCount; ++j)
		{
			Vertex v;
			float x = sin(M_PI * j / pi_longitudeCount) * cos(2 * M_PI * i / pi_latitudeCount);
			float y = sin(M_PI * j / pi_longitudeCount) * sin(2 * M_PI * i / pi_latitudeCount);
			float z = cos(M_PI * j / pi_longitudeCount);
			v.m_position = { x, y, z };
			mesh->m_vertices.emplace_back(v);
		}
	}
	return mesh;
}
