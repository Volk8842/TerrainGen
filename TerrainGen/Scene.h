#ifndef SCENE_H
#define SCENE_H

#include "OpenGLWindow.h"
#include "Graphic2DObject.h"

class Graphic2DObject;

class OpenGLWindow;

class Scene
{
public:
	Scene();

	void setWindow(OpenGLWindow* window);

	void render();
	void prepareToRender();

private:
	OpenGLWindow* m_window;
	ShaderProgram* m_shaderProgram;
	Graphic2DObject* obj;

};

#endif //SCENE_H