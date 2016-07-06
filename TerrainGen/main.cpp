#include <iostream>
#include <fstream>
#include <sstream>

#include "OpenGLWindow.h"
#include "Scene.h"

int main() {
	Scene scene;
	OpenGLWindow window;
	window.setScene(&scene);
	window.startMainLoop();
	return 0;
}