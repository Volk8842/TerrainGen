#include <iostream>
#include <fstream>
#include <sstream>

#include "MainWindow.h"
#include "Scene.h"

int main() {
	Scene scene;
	MainWindow mainWindow;
	mainWindow.setScene(&scene);
	mainWindow.startMainLoop();
	return 0;
}