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

	void Convert2Dto3D(Vertex& m_inPoint);
	void RenderScene(Scene* m_scene, Texture& m_Target, SDL_Renderer* p_Renderer);
	void ZBuffer(unsigned int p_x, unsigned int p_y, Triangle & p_triangle, Texture& p_texture);
};

