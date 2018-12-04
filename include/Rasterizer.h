#pragma once
#include <Scene.h>
#include <Texture.h>
#include <SDL.h>

class Rasterizer
{
public:
	Rasterizer();
	~Rasterizer();

	void RenderScene(int v0x, int v0y, int v1x, int v1y, Texture& m_Target, SDL_Renderer* p_Renderer, Scene* p_scene);
	void ZBuffer(Texture * p_texture, Scene * p_scene);
};

