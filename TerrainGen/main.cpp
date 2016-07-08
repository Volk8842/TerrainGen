#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

#include "OpenGLWindow.h"
#include "Scene.h"

int main() {
	srand(time(0));
	OpenGLWindow window;
	Scene scene;
	window.setScene(&scene);
	window.startMainLoop();
	return 0;
}