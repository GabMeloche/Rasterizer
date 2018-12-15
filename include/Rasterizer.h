#pragma once
#include <Scene.h>
#include <Texture.h>
#include <SDL.h>

class Rasterizer
{
private:
	float** m_zBuffer;
public:
	Rasterizer();
	~Rasterizer();
	
	SDL_Renderer* p_renderer;
	void Convert2Dto3D(Vertex& m_inPoint);
	void RenderScene(Scene* m_scene, Texture& m_Target);
	void ZBuffer(unsigned int p_x, unsigned int p_y, Triangle & p_triangle, Texture& p_texture);
	Vec3 GetPixelPos(Vec4 & p_v);
	void ClearZBuffer();
	void FillTriangles(Vec3& v1, Vec3& v2, Vec3& v3, int top);
};

