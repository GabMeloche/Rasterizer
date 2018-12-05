#pragma once
#include <Scene.h>
#include <Texture.h>
#include <SDL.h>

class Rasterizer
{
public:
	Rasterizer();
	~Rasterizer();

	void Convert2Dto3D(Vertex& m_inPoint);
	void RenderScene(Scene* m_scene, Texture& m_Target, SDL_Renderer* p_Renderer);
	void ZBuffer(Texture * p_texture, Scene * p_scene);
};

