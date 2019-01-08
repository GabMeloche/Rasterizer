#pragma once
#include <Scene.h>
#include <Texture.h>
#include <SDL.h>

class Rasterizer
{
private:
	float** m_zBuffer;
	Texture* m_texture;
	Scene* m_scene;
	SDL_Renderer* m_renderer;

public:
	Rasterizer();
	~Rasterizer();

	void setTexture(Texture * p_texture);
	void setScene(Scene* p_scene);
	void setRenderer(SDL_Renderer * p_renderer);
	void RenderScene(Scene* m_scene, Texture& m_Target);
	bool ZBuffer(unsigned int p_x, unsigned int p_y, float p_z);
	Vec3 PixelPosRatio(Vec4 & p_v);
	void ClearZBuffer();
	void FillTriangles(Vec3 & v1, Vec3 & v2, Vec3 & v3, Color& p_color, Triangle& p_triangle);
};

