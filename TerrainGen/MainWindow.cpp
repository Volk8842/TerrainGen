#include "MainWindow.h"
#include "GraphicObject.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

MainWindow::MainWindow() 
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

MainWindow::~MainWindow()
{
	glfwTerminate();
}

void MainWindow::setScene(Scene* scene)
{
	m_scene = scene;
}

void MainWindow::startMainLoop()
{
//	GraphicObject obj;
	
	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
//		obj.draw();

		m_scene->draw();

		glfwSwapBuffers(m_window);
	}
}