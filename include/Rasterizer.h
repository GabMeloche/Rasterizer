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

public:
	Rasterizer();
	~Rasterizer();

	void setTexture(Texture * p_texture);
	void setScene(Scene* p_scene);
	SDL_Renderer* p_renderer;
	void Convert2Dto3D(Vertex& m_inPoint);
	void RenderScene(Scene* m_scene, Texture& m_Target);
	bool ZBuffer(unsigned int p_x, unsigned int p_y, float p_z);
	Vec3 GetPixelPos(Vec4 & p_v);
	void ClearZBuffer();
	void FillTriangles(Vec3& v1, Vec3& v2, Vec3& v3, float p_z, Color& p_color, Triangle& p_triangle);
	void CalculateLight(unsigned int p_x, unsigned int p_y, Light & p_light, Triangle & p_triangle);
};

