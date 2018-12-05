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

	void RenderScene(Scene* m_scene, Texture& m_Target, SDL_Renderer* p_Renderer);
	void ZBuffer(Texture * p_texture, Scene * p_scene);
};

