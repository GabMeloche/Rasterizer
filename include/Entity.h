#pragma once
#include <Mesh.h>
#include <Math/Matrix/Mat4.h>

class Entity
{
private:
	Mesh* m_mesh;
	Math::Matrix::Mat4 m_mat;
public:
	Entity() = default;
	~Entity();
	Entity(const Entity& p_other);

	void setMesh(Mesh* mesh);
	Mesh* getMesh();
};
