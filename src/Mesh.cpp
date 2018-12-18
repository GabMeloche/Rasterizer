#define _USE_MATH_DEFINES
#include <Mesh.h>
#include <Vertex.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <cassert>

Mesh* Mesh::CreateCube(const float p_Size)
{
	Mesh* mesh = new Mesh;

	float fPointPos = p_Size / 2.0f;

	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -fPointPos, fPointPos, -fPointPos } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ fPointPos, fPointPos, -fPointPos } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ fPointPos, -fPointPos, -fPointPos } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -fPointPos, -fPointPos, -fPointPos } });

	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -fPointPos, fPointPos, fPointPos } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ fPointPos, fPointPos, fPointPos } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ fPointPos, -fPointPos, fPointPos } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -fPointPos, -fPointPos, fPointPos } });

	//mesh->makeTriangles();
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[0], 
											mesh->m_vertices[1], 
											mesh->m_vertices[2] });
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[0],
											mesh->m_vertices[3],
											mesh->m_vertices[2] }); //front 

	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[5],
											mesh->m_vertices[4],
											mesh->m_vertices[0] });
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[5],
											mesh->m_vertices[1],
											mesh->m_vertices[0] }); //top

	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[0], 
											mesh->m_vertices[3],
											mesh->m_vertices[7] });
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[0],
											mesh->m_vertices[4],
											mesh->m_vertices[7] }); //left

	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[5],
											mesh->m_vertices[4],
											mesh->m_vertices[7] });
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[5],
											mesh->m_vertices[6],
											mesh->m_vertices[7] }); //back

	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[1],
											mesh->m_vertices[5],
											mesh->m_vertices[6] });
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[1],
											mesh->m_vertices[2],
											mesh->m_vertices[6] }); //right

	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[3],
											mesh->m_vertices[7],
											mesh->m_vertices[6] });
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[3],
											mesh->m_vertices[2],
											mesh->m_vertices[6] }); //bottom
		
	for (int i = 0; i < mesh->m_triangles.size(); ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			mesh->m_triangles[i][j].m_pos = new Vec4(mesh->m_triangles[i][j].m_position);
			mesh->m_triangles[i][j].m_color = { static_cast<unsigned int>(rand() % 255),
												static_cast<unsigned int>(rand() % 255),
												static_cast<unsigned int>(rand() % 255), 255 };
		}
	}

	mesh->Normalize();
	return mesh;
}

Mesh * Mesh::CreateSphere(int pi_latitudeCount, int pi_longitudeCount)
{
	Mesh* mesh = new Mesh;

	const float t = (1.0f + std::sqrt(5.0f)) / 2.0f;

	// Vertices
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -1.0, t, 0.0 } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ 1.0, t, 0.0 } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -1.0, -t, 0.0 } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ 1.0, -t, 0.0 } });
	
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ 0.0, -1.0, t } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ 0.0, 1.0, t } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ 0.0, -1.0, -t } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ 0.0, 1.0, -t } });
	
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ t, 0.0, -1.0 } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ t, 0.0, 1.0 } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -t, 0.0, -1.0 } });
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -t, 0.0, 1.0 } });

	// Faces
	//mesh->m_triangles.emplace_back(0, 11, 5);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[0],
											mesh->m_vertices[11],
											mesh->m_vertices[5] });
	//mesh.addTriangle(0, 5, 1);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[0],
											mesh->m_vertices[5],
											mesh->m_vertices[1] });
	//mesh.addTriangle(0, 1, 7);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[0],
											mesh->m_vertices[1],
											mesh->m_vertices[7] });

	//mesh.addTriangle(0, 7, 10);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[0],
											mesh->m_vertices[7],
											mesh->m_vertices[10] });
	//mesh.addTriangle(0, 10, 11);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[0],
											mesh->m_vertices[10],
											mesh->m_vertices[11] });
	//mesh.addTriangle(1, 5, 9);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[1],
											mesh->m_vertices[5],
											mesh->m_vertices[9] });
	//mesh.addTriangle(5, 11, 4);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[5],
											mesh->m_vertices[11],
											mesh->m_vertices[4] });
	//mesh.addTriangle(11, 10, 2);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[11],
											mesh->m_vertices[10],
											mesh->m_vertices[2] });
	//mesh.addTriangle(10, 7, 6);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[10],
											mesh->m_vertices[7],
											mesh->m_vertices[6] });
	//mesh.addTriangle(7, 1, 8);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[7],
											mesh->m_vertices[1],
											mesh->m_vertices[8] });
	//mesh.addTriangle(3, 9, 4);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[3],
											mesh->m_vertices[9],
											mesh->m_vertices[4] });
	//mesh.addTriangle(3, 4, 2);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[3],
											mesh->m_vertices[4],
											mesh->m_vertices[2] });
	//mesh.addTriangle(3, 2, 6);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[3],
											mesh->m_vertices[2],
											mesh->m_vertices[6] });
	//mesh.addTriangle(3, 6, 8);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[3],
											mesh->m_vertices[6],
											mesh->m_vertices[8] });
	//mesh.addTriangle(3, 8, 9);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[3],
											mesh->m_vertices[8],
											mesh->m_vertices[9] });
	//mesh.addTriangle(4, 9, 5);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[4],
											mesh->m_vertices[9],
											mesh->m_vertices[5] });
	//mesh.addTriangle(2, 4, 11);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[2],
											mesh->m_vertices[4],
											mesh->m_vertices[11] });
	//mesh.addTriangle(6, 2, 10);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[6],
											mesh->m_vertices[2],
											mesh->m_vertices[10] });
	//mesh.addTriangle(8, 6, 7);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[8],
											mesh->m_vertices[6],
											mesh->m_vertices[7] });
	//mesh.addTriangle(9, 8, 1);
	mesh->m_triangles.emplace_back(Triangle{ mesh->m_vertices[9],
											mesh->m_vertices[8],
											mesh->m_vertices[1] });

	//number of subTriangle in sphere
	int recursionLevel = 1;

	// refine triangle (add more triangle for more spheric apparence)
	for (int i = 0; i < recursionLevel; i++)
	{
		Mesh* mesh2 = new Mesh;

		for (auto tri : mesh->getTriangles())
		{
			Vertex a = GetMiddlePoint(tri.m_v1, tri.m_v2);
			Vertex b = GetMiddlePoint(tri.m_v2, tri.m_v3);
			Vertex c = GetMiddlePoint(tri.m_v3, tri.m_v1);

			mesh2->m_triangles.emplace_back(Triangle{ tri.m_v1, a, c});
			mesh2->m_triangles.emplace_back(Triangle{ tri.m_v2, b, a});
			mesh2->m_triangles.emplace_back(Triangle{ tri.m_v3, c, b});
			mesh2->m_triangles.emplace_back(Triangle{ a, b, c});
		}

		mesh = mesh2;

	}

	for (int i = 0; i < mesh->m_triangles.size(); ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			mesh->m_triangles[i][j].m_pos = new Vec4(mesh->m_triangles[i][j].m_position);
			mesh->m_triangles[i][j].m_color = { static_cast<unsigned int>(rand() % 255),
												static_cast<unsigned int>(rand() % 255),
												static_cast<unsigned int>(rand() % 255), 255 };
		}
	}

	mesh->Normalize();

	return mesh;
}

Vertex Mesh::GetMiddlePoint(Vertex& v1, Vertex& v2)
{
	Vertex middle;

	middle.m_position.mf_x = (v1.m_position.mf_x + v2.m_position.mf_x) / 2.0f;
	middle.m_position.mf_y = (v1.m_position.mf_y + v2.m_position.mf_y) / 2.0f;
	middle.m_position.mf_z = (v1.m_position.mf_z + v2.m_position.mf_z) / 2.0f;

	return middle;
}

void Mesh::Normalize()
{
	for (int i = 0; i < m_vertices.size(); ++i)
	{
		m_vertices[i].m_normal = Vec3();
	}

	for (int i = 0; i < m_triangles.size(); ++i)
	{
		Vec3 e1 = m_triangles[i][0].m_position - m_triangles[i][1].m_position;
		Vec3 e2 = m_triangles[i][2].m_position - m_triangles[i][1].m_position;
		Vec3 no = Vec3::crossProduct(e1, e2);

		m_triangles[i][0].m_normal += no;
		m_triangles[i][0].m_normal.Normalize();
		m_triangles[i][1].m_normal += no;
		m_triangles[i][1].m_normal.Normalize();
		m_triangles[i][2].m_normal += no;
		m_triangles[i][2].m_normal.Normalize();
	}
}

std::vector<Triangle>& Mesh::getTriangles()
{
	return m_triangles;
}

std::vector<Vertex>& Mesh::getVertices()
{
	return m_vertices;
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
