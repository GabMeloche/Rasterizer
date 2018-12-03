#define _USE_MATH_DEFINES
#include <Mesh.h>
#include <Vertex.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <cassert>

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

	mesh->makeTriangles();
	/*mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[0], 
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
		mesh->m_vertices[6] }); //bottom*/

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
			std::cout << "x: " << x << "; y: " << y << "; z: " << z << std::endl;
			mesh->m_vertices.emplace_back(v);
		}
	}
	mesh->makeTriangles();
	return mesh;
}

void Mesh::makeTriangles()
{
	//TODO : Need to sort vertices ordre croissant before operations

	for (size_t i = 0; i < m_vertices.size(); ++i)
	{
		float shortestDist1 = Vec3::DistanceBtwPts(m_vertices[i].m_position, m_vertices
			[i == 0 ? 2 : 0].m_position);;
		float shortestDist2 = Vec3::DistanceBtwPts(m_vertices[i].m_position, m_vertices
			[i == 1 ? 0 : 1].m_position);;
		int indice1 = 0;
		int indice2 = 1;

		for (size_t j = 2; j < m_vertices.size(); ++j)
		{
			if (j == i)
				continue;

			float distance = Vec3::DistanceBtwPts(m_vertices[i].m_position, m_vertices[j].m_position);

			if (distance <= shortestDist2 && distance > shortestDist1 && distance != 0.0f)
			{
				shortestDist2 = distance;
				indice2 = (int)j;
			}
			if (distance <= shortestDist1 && distance != 0.0f)
			{
				shortestDist1 = distance;
				indice1 = (int)j;
			}
			
		}
		std::cout << "Triangle " << i << " goes with: " << indice1 << ", " << indice2 << std::endl;
		m_triangles.emplace_back(Triangle{ m_vertices[i],
			m_vertices[indice1],
			m_vertices[indice2] });
	}

	std::cout << "Number of triangles: " << m_triangles.size() << std::endl;
}
