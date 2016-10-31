
#include <Controllers/DefaultController.h>
#include <SphereGenerator.h>
#include <OpenGLApplication.h>
#include <string>
#include <opengl.h>
#include <CameraManager.h>
#include <Debug.h>

void DefaultController::onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
	debug::log("key: " + std::to_string(key)
		+ ", scancode: " + std::to_string(scancode)
		+ ", action: " + std::to_string(action)
		+ ", mods: " + std::to_string(mods));
}

void DefaultController::onCharPressed(GLFWwindow* window, unsigned int codepoint, int mods) {
	debug::log("codepoint: " + std::to_string(codepoint)
		+ ", mods: " + std::to_string(mods));
}

void DefaultController::onCursorMoved(GLFWwindow* window, double xpos, double ypos) {
	debug::log("xpos: " + std::to_string(xpos)
		+ ", ypos: " + std::to_string(ypos));

	if (isRightButtonPressed) {
		CameraManager::getInstance()->getCamera()->rotateCamera(lastXPos - xpos, lastYPos - ypos);
		lastXPos = xpos;
		lastYPos = ypos;
		//glfwSetCursorPos(window, xpos, ypos);
	}
}

void DefaultController::onMouseButtonPressed(GLFWwindow* window, int button, int action, int mods) {
	debug::log("button: " + std::to_string(button)
		+ ", action: " + std::to_string(action)
		+ ", mods: " + std::to_string(mods));
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			glfwGetCursorPos(window, &lastXPos, &lastYPos);
			glfwSetInputMode(OpenGLApplication::getInstance()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			isRightButtonPressed = true;
		}
		else {
			glfwSetInputMode(OpenGLApplication::getInstance()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			isRightButtonPressed = false;
		}
	}
}

void DefaultController::onScroll(GLFWwindow* window, double xoffset, double yoffset) {
	debug::log("xoffset: " + std::to_string(xoffset)
		+ ", yoffset: " + std::to_string(yoffset));
}

void DefaultController::draw() {
	static int timer = 0;
	if (timer < 60) timer++;
	else {
		timer = 0;
//		LandscapeGenerator::useThermalErrosion(*map, 0.5f / map->halfSideWidth());
	}
	graphic2DObject->render();
}

DefaultController::DefaultController() {
	//map = LandscapeGenerator::createHeightMap(8);
	graphic2DObject = SphereGenerator::createGraphicRepresentation();
	graphic2DObject->prepareToRender();
	
}