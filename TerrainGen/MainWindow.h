#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "opengl.h"

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