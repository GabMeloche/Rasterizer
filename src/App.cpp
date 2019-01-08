#include <App.h>
#include <iostream>
#include <Texture.h>
#include <Rasterizer.h>
#include <Triangle.h>
#include <Entity.h>

App::App()
{
	m_window = SDL_CreateWindow("RASTERIZER",   SDL_WINDOWPOS_CENTERED,
												SDL_WINDOWPOS_CENTERED,
												1024, 768,
												SDL_WINDOW_SHOWN);

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_rasterizer = new Rasterizer;
	m_texture = new Texture(1024, 768);
	m_scene = new Scene;
	m_rasterizer->setRenderer(m_renderer);
	m_rasterizer->setTexture(m_texture);
	m_rasterizer->setScene(m_scene);
}


App::~App()
{
}

void App::Startup()
{
	Mesh* cube = new Mesh;
	Mesh* cube2 = new Mesh;
	cube = Mesh::CreateSphere(1);
	cube2 = Mesh::CreateCube(1);

	Light light = Light();

	Entity* entity = new Entity;
	Entity* entity2 = new Entity;
	entity->setMesh(cube);
	entity2->setMesh(cube2);

	m_scene->getLights().emplace_back(light);
	m_scene->getEntities().emplace_back(entity);
	m_scene->getEntities().emplace_back(entity2);

	MainLoop();
}

void App::MainLoop()
{
	bool is_over = false;
	while (is_over == false)
	{
		SDL_PollEvent(&m_event);
		Clear();
		if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_ESCAPE || m_event.type == SDL_QUIT)
		{
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			is_over = true;
		}
		m_rasterizer->RenderScene(m_scene, *m_texture);
		Render();
	}
}
void App::Clear()
{
	SDL_SetRenderDrawColor(m_renderer, 25, 25, 25, 255);
	SDL_RenderClear(m_renderer);
}
void App::Render()
{
	SDL_RenderPresent(m_renderer);
}




