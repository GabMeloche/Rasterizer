#include <Mesh.h>
#include <Vertex.h>
#include <vector>

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

	return nullptr;
}
