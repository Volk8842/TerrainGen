#include "OpenGLWindow.h"
#include "GraphicObject.h"
#include "Graphic2DObject.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

OpenGLWindow::OpenGLWindow()
	:m_width(640), m_height(480)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	m_window = glfwCreateWindow(m_width, m_height, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(m_window);

	// TODO: callbacks
	glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = GL_TRUE;
	glewInit();

	int viewportWidth;
	int viewportHeight;

	glfwGetFramebufferSize(m_window, &viewportWidth, &viewportHeight);
	glViewport(0, 0, viewportWidth, viewportHeight);

	glEnable(GL_DEPTH_TEST);
}

OpenGLWindow::~OpenGLWindow()
{
	glfwTerminate();
}

void OpenGLWindow::setScene(Scene* scene)
{
	m_scene = scene;
	m_scene->setWindow(this);
}

void OpenGLWindow::startMainLoop()
{
	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (m_scene != nullptr) {
			m_scene->prepareToRender();
			m_scene->render();
		}
		glfwSwapBuffers(m_window);
	}
}

GLuint OpenGLWindow::width()
{
	return m_width;
}

GLuint OpenGLWindow::height()
{
	return m_height;
}

Scene* OpenGLWindow::scene()
{
	return m_scene;
}