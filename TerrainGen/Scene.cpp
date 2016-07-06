#include "Scene.h"
#include "LandscapeSector.h"

Scene::Scene()
{
	obj = new LandscapeSector(this);
}

void Scene::setWindow(OpenGLWindow* window)
{
	m_window = window;
}

void Scene::prepareToRender()
{
	obj->prepareToRender();
}

void Scene::render()
{
	obj->render();
}

