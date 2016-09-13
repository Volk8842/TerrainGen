#include "Controllers/DefaultController.h"
#include "Debug.h"
#include <string>

void DefaultController::onKeyPressed(int key, int scancode, int action, int mods) {
	debug::log("key: " + std::to_string(key)
		+ ", scancode: " + std::to_string(scancode)
		+ ", action: " + std::to_string(action)
		+ ", mods: " + std::to_string(mods));
}

void DefaultController::onCharPressed(unsigned int codepoint, int mods) {
	debug::log("codepoint: " + std::to_string(codepoint)
		+ ", mods: " + std::to_string(mods));
}

void DefaultController::onCursorMoved(double xpos, double ypos) {
	debug::log("xpos: " + std::to_string(xpos)
		+ ", ypos: " + std::to_string(ypos));
}

void DefaultController::onMouseButtonPressed(int button, int action, int mods) {
	debug::log("button: " + std::to_string(button)
		+ ", action: " + std::to_string(action)
		+ ", mods: " + std::to_string(mods));
}

void DefaultController::onScroll(double xoffset, double yoffset) {
	debug::log("xoffset: " + std::to_string(xoffset)
		+ ", yoffset: " + std::to_string(yoffset));
}
