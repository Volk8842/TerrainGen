#ifndef DEFAULT_CONTROLLER_H
#define DEFAULT_CONTROLLER_H

#include <Controllers/IController.h>
#include <Graphic2DObject.h>

class DefaultController: public IController {
public:
	virtual void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
	virtual void onCharPressed(GLFWwindow* window, unsigned int codepoint, int mods);
	virtual void onCursorMoved(GLFWwindow* window, double xpos, double ypos);
	virtual void onMouseButtonPressed(GLFWwindow* window, int button, int action, int mods);
	virtual void onScroll(GLFWwindow* window, double xoffset, double yoffset);
	virtual void draw();

public:
	DefaultController();

private:
	bool isRightButtonPressed;
	double lastXPos;
	double lastYPos;

	Graphic2DObject* graphic2DObject;
};

#endif //DEFAULT_CONTROLLER_H