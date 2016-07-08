#include "Scene.h"
#include "Landscape.h"

Scene::Scene()
{
	Landscape land;
	m_shaderProgram = new ShaderProgram();
	m_shaderProgram->compileShaderProgram("2DHeightMap.vert", "2DHeightMap.frag");
	obj = land.createGraphicRepresentation();
	obj->setShaderProgram(m_shaderProgram);
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

