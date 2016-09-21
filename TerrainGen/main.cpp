#include <OpenGLApplication.h>
#include <ctime>

int main() {
	srand(time(0));
	OpenGLApplication* app = OpenGLApplication::getInstance();
	app->start();
	return 0;
}