#define _USE_MATH_DEFINES
#include <Mesh.h>
#include <Vertex.h>
#include <vector>
#include <cmath>
#include <cassert>

Mesh* Mesh::CreateCube(const float p_Size)
{
	Mesh* mesh = new Mesh;

	float fPointPos = p_Size / 2.0f;

	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -fPointPos, fPointPos, -fPointPos } }); //0
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ fPointPos, fPointPos, -fPointPos } }); //1
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ fPointPos, -fPointPos, -fPointPos } }); //2
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -fPointPos, -fPointPos, -fPointPos } }); //3

	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -fPointPos, fPointPos, fPointPos } }); //4
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ fPointPos, fPointPos, fPointPos } }); //5
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ fPointPos, -fPointPos, fPointPos } }); //6
	mesh->m_vertices.emplace_back(Vertex{ Vec3{ -fPointPos, -fPointPos, fPointPos } }); //7

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
		mesh->m_triangles[i].m_color = { 255, 0, 0, 255 };
		
		for (int j = 0; j < 3; ++j)
		{
			mesh->m_triangles[i][j].m_pos = new Vec4(mesh->m_triangles[i][j].m_position);
		}
	}

	mesh->CreateNormals();
	return mesh;
}

Mesh * Mesh::CreateSphere(const float p_Size, const int precision)
{
	Mesh* mesh = new Mesh;

	mesh = CreateCube(p_Size);

	//number of subTriangle in sphere
	int recursionLevel = precision;
	float radius = p_Size / 1.16279069767f;

	// refine triangle (add more triangle for more spheric apparence)
	for (int i = 0; i < recursionLevel; i++)
	{
		Mesh* mesh2 = new Mesh;

		for (auto tri : mesh->getTriangles())
		{
			Vertex a = GetMiddlePoint(tri.m_v1, tri.m_v2);
			Vertex b = GetMiddlePoint(tri.m_v2, tri.m_v3);
			Vertex c = GetMiddlePoint(tri.m_v3, tri.m_v1);

			////get magnitude
			float magnA = sqrt(pow(a.m_position.mf_x, 2.0f) + pow(a.m_position.mf_y, 2.0f) + pow(a.m_position.mf_z, 2.0f));
			float magnB = sqrt(pow(b.m_position.mf_x, 2.0f) + pow(b.m_position.mf_y, 2.0f) + pow(b.m_position.mf_z, 2.0f));
			float magnC = sqrt(pow(c.m_position.mf_x, 2.0f) + pow(c.m_position.mf_y, 2.0f) + pow(c.m_position.mf_z, 2.0f));

			a.m_position.mf_x *= (radius / magnA);
			a.m_position.mf_y *= (radius / magnA);
			a.m_position.mf_z *= (radius / magnA);

			b.m_position.mf_x *= (radius / magnB);
			b.m_position.mf_y *= (radius / magnB);
			b.m_position.mf_z *= (radius / magnB);

			c.m_position.mf_x *= (radius / magnC);
			c.m_position.mf_y *= (radius / magnC);
			c.m_position.mf_z *= (radius / magnC);

			mesh2->m_triangles.emplace_back(Triangle{ tri.m_v1, a, c});
			mesh2->m_triangles.emplace_back(Triangle{ b, tri.m_v2, a});
			mesh2->m_triangles.emplace_back(Triangle{ c, b, tri.m_v3});
			mesh2->m_triangles.emplace_back(Triangle{ a, b, c});
		
		}

		mesh = mesh2;

	}

	for (int i = 0; i < mesh->m_triangles.size(); ++i)
	{
		mesh->m_triangles[i].m_color = { 255, 0, 0, 255 };
		for (int j = 0; j < 3; ++j)
		{
			mesh->m_triangles[i][j].m_pos = new Vec4(mesh->m_triangles[i][j].m_position);
		}
	}

	mesh->CreateNormals();

	return mesh;
}

Vertex Mesh::GetMiddlePoint(Vertex& v1, Vertex& v2)
{
	Vertex middle;
	Vertex a = v1;
	Vertex b = v2;

	middle.m_position.mf_x = (a.m_position.mf_x + b.m_position.mf_x) / 2.0f;
	middle.m_position.mf_y = (a.m_position.mf_y + b.m_position.mf_y) / 2.0f;
	middle.m_position.mf_z = (a.m_position.mf_z + b.m_position.mf_z) / 2.0f;

	return middle;
}

void Mesh::CreateNormals()
{

	for (int i = 0; i < m_triangles.size(); ++i)
	{

		Vec3 e1 = m_triangles[i][2].m_position - m_triangles[i][1].m_position;
		Vec3 e2 = m_triangles[i][0].m_position - m_triangles[i][1].m_position;

		Vec3 cross = Vec3::crossProduct(e1, e2);
		cross.Normalize();

		m_triangles[i].m_normal = cross;
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
