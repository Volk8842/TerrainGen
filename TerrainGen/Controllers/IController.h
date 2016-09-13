#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <opengl.h>

class IController {
public:
	virtual void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
	virtual void onCharPressed(GLFWwindow* window, unsigned int codepoint, int mods) = 0;
	virtual void onCursorMoved(GLFWwindow* window, double xpos, double ypos) = 0;
	virtual void onMouseButtonPressed(GLFWwindow* window, int button, int action, int mods) = 0;
	virtual void onScroll(GLFWwindow* window, double xoffset, double yoffset) = 0;
	virtual void draw() = 0;
};

#endif //ICONTROLLER_H