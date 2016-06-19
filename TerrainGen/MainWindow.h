#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "opengl.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class MainWindow 
{
public:
	MainWindow();
	~MainWindow();

	void startMainLoop();

private:
	GLFWwindow* m_window;
	GLuint m_width;
	GLuint m_height;
	int m_viewportWidth;
	int m_viewportHeight;
};

#endif //MAINWINDOW_H