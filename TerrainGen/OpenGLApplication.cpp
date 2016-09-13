#include <OpenGLApplication.h>
#include <Controllers/DefaultController.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	auto controller = OpenGLApplication::getInstance()->getController();
	if (controller != nullptr)
		controller->onKeyPressed(window, key, scancode, action, mods);
}

void charmods_callback(GLFWwindow* window, unsigned int codepoint, int mods) {
	auto controller = OpenGLApplication::getInstance()->getController();
	if (controller != nullptr)
		controller->onCharPressed(window, codepoint, mods);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	auto controller = OpenGLApplication::getInstance()->getController();
	if (controller != nullptr)
		controller->onCursorMoved(window, xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	auto controller = OpenGLApplication::getInstance()->getController();
	if (controller != nullptr)
		controller->onMouseButtonPressed(window, button, action, mods);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	auto controller = OpenGLApplication::getInstance()->getController();
	if (controller != nullptr)
		controller->onScroll(window, xoffset, yoffset);
}

OpenGLApplication* OpenGLApplication::m_application = nullptr;

GLFWwindow* OpenGLApplication::getWindow() {
	return m_window;
}

OpenGLApplication* OpenGLApplication::getInstance() {
	if (m_application == nullptr) 
		m_application = new OpenGLApplication();
	return m_application;
}

OpenGLApplication::OpenGLApplication() {
	createOpenGLContext();
	m_controller = new DefaultController();
}

OpenGLApplication::~OpenGLApplication() {
	glfwTerminate();
}

void OpenGLApplication::createOpenGLContext() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	m_window = glfwCreateWindow(640, 480, "OpenGLApplication", nullptr, nullptr);
	glfwMakeContextCurrent(m_window);

	int viewportWidth;
	int viewportHeight;
	glfwGetFramebufferSize(m_window, &viewportWidth, &viewportHeight);
	glViewport(0, 0, viewportWidth, viewportHeight);

	glfwSetKeyCallback(m_window, key_callback);
	glfwSetCharModsCallback(m_window, charmods_callback);
	glfwSetCursorPosCallback(m_window, cursor_position_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	glfwSetScrollCallback(m_window, scroll_callback);

	glfwSetCursorPos(m_window, 320, 240);

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
}

void OpenGLApplication::start() {
	while (!glfwWindowShouldClose(m_window)) {
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_controller->draw();

		glfwSwapBuffers(m_window);
	}
}

IController* OpenGLApplication::getController() {
	return m_controller;
}
