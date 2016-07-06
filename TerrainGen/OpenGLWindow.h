#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include "opengl.h"
#include "Scene.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Scene;

class OpenGLWindow
{
public:
	OpenGLWindow();
	~OpenGLWindow();

	void setScene(Scene* scene);

	void startMainLoop();

	GLuint width();
	GLuint height();
	Scene* scene();

private:
	GLFWwindow* m_window;
	GLuint m_width;
	GLuint m_height;

	Scene* m_scene;
};

#endif //OPENGL_WINDOW_H