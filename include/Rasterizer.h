#pragma once
#include <Scene.h>
#include <Texture.h>
#include <SDL.h>

class Rasterizer
{
public:
	Rasterizer();
	~Rasterizer();

	void RenderScene(Scene* m_Scene, Texture* m_Target, SDL_Renderer* p_Renderer);
};

