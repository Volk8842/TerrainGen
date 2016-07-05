#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "opengl.h"
#include "Scene.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class MainWindow 
{
public:
	MainWindow();
	~MainWindow();

	void startMainLoop();
	void setScene(Scene* scene);

private:
	GLFWwindow* m_window;
	GLuint m_width;
	GLuint m_height;

	Scene* m_scene;
};

#endif //MAINWINDOW_H