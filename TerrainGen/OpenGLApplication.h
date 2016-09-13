#ifndef OPENGL_APPLICATION_H
#define OPENGL_APPLICATION_H

#include <opengl.h>
#include <Controllers/IController.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void charmods_callback(GLFWwindow* window, unsigned int codepoint, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

class OpenGLApplication {
	
public:
	static OpenGLApplication* getInstance();
	~OpenGLApplication();

	GLFWwindow* getWindow();
	IController* getController();
	void start();

private:
	static OpenGLApplication* m_application;

	OpenGLApplication();
	void createOpenGLContext();

	GLFWwindow* m_window;
	IController* m_controller;
};

#endif //OPENGL_APPLICATION_H