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
	mesh->m_vertices.emplace_back(Vertex{ Vec3{-0.5f, -0.5f, 0.0f} });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{0.5f, -0.5f, 0.0f} });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{0.5f, 0.5f, 0.0f} });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -0.5f, 0.5f, 1.0f } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -0.5f, -0.5f, 1.0f } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ 0.5f, -0.5f, 1.0f } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ 0.5f, 0.5f, 1.0f } });

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
		mesh->m_vertices[6] }); //bottom
		*/
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

Mesh * Mesh::CreateTriangle(int x, int y, int z)
{
	Mesh* mesh = new Mesh;
	Triangle m_triangle;

	//RED PIXEL
	m_triangle.m_v1.m_position.mf_x = x;
	m_triangle.m_v1.m_position.mf_y = y;
	m_triangle.m_v1.m_position.mf_z = z;

	/*m_texture->m_pixels[500 + 200 * m_texture->mui_w].ucm_r = 255;
	m_texture->m_pixels[500 + 200 * m_texture->mui_w].ucm_g = 0;
	m_texture->m_pixels[500 + 200 * m_texture->mui_w].ucm_b = 0;*/

	//GREEN PIXEL
	m_triangle.m_v2.m_position.mf_x = x - 250;
	m_triangle.m_v2.m_position.mf_y = y + 400;
	m_triangle.m_v2.m_position.mf_z = z;
	/*m_texture->m_pixels[250 + 600 * m_texture->mui_w].ucm_r = 0;
	m_texture->m_pixels[250 + 600 * m_texture->mui_w].ucm_g = 255;
	m_texture->m_pixels[250 + 600 * m_texture->mui_w].ucm_b = 0;*/

	//BLUE PIXEL
	m_triangle.m_v3.m_position.mf_x = x + 250;
	m_triangle.m_v3.m_position.mf_y = y + 400;
	m_triangle.m_v3.m_position.mf_z = z;
	/*m_texture->m_pixels[750 + 600 * m_texture->mui_w].ucm_r = 0;
	m_texture->m_pixels[750 + 600 * m_texture->mui_w].ucm_g = 0;
	m_texture->m_pixels[750 + 600 * m_texture->mui_w].ucm_b = 255;*/

	mesh->m_triangles.push_back(m_triangle);

	return mesh;
}

std::vector<Triangle> Mesh::getTriangles()
{
	return m_triangles;
}

std::vector<Vertex> Mesh::getVertices()
{
	return m_vertices;
}

void Mesh::makeTriangles()
{
	this->sort();

	for (size_t i = 0; i < m_vertices.size(); ++i)
	{
		float shortestDist1 = Vec3::DistanceBtwPts(m_vertices[i].m_position, m_vertices
			[i == 0 ? 2 : 0].m_position);
		float shortestDist2 = Vec3::DistanceBtwPts(m_vertices[i].m_position, m_vertices
			[i == 1 ? 0 : 1].m_position);

		int indice1 = 0;
		int indice2 = 1;
		std::vector<Vertex> tmpTriangle;
		tmpTriangle.emplace_back(m_vertices[i]);

		for (size_t j = 0; j < m_vertices.size(); ++j)
		{
			if (j == i)
				continue;

			float distance = Vec3::DistanceBtwPts(m_vertices[i].m_position, m_vertices[j].m_position);

			if (distance <= shortestDist2 && distance > shortestDist1 && distance != 0.0f)
			{
				shortestDist2 = distance;
				indice2 = (int)j;
				tmpTriangle.emplace_back(m_vertices[j]);
			}
			if (distance <= shortestDist1 && distance != 0.0f)
			{
				shortestDist1 = distance;
				indice1 = (int)j;
				tmpTriangle.emplace_back(m_vertices[j]);
			}
			if (tmpTriangle.size() == 3)
			{
				m_triangles.emplace_back(Triangle{tmpTriangle[0], tmpTriangle[1], tmpTriangle[2]});
				std::cout << "Triangle " << i << " goes with: " << indice1 << ", " << indice2 << std::endl;
				tmpTriangle.clear();

			}
			
		}
		/*m_triangles.emplace_back(Triangle{ m_vertices[i],
			m_vertices[indice1],
			m_vertices[indice2] });*/
	}

	std::cout << "Number of triangles: " << m_triangles.size() << std::endl;
}

void Mesh::sort()
{
	for (size_t i = 0; i < m_vertices.size() - 1; ++i)
	{
		for (size_t j = 0; j < m_vertices.size() - i - 1; ++j)
		{
			if (m_vertices[j + 1] < m_vertices[j])
			{
				Vertex tmp = m_vertices[j + 1];
				m_vertices[j + 1] = m_vertices[j];
				m_vertices[j] = tmp;
			}
		}
	}
}
