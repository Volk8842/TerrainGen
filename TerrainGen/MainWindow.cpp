#include "MainWindow.h"

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

	glewExperimental = GL_TRUE;
	glewInit();

	glfwGetFramebufferSize(m_window, &m_viewportWidth, &m_viewportHeight);
	glViewport(0, 0, m_viewportWidth, m_viewportHeight);
}

MainWindow::~MainWindow()
{
	glfwTerminate();
}

void MainWindow::startMainLoop()
{
	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(m_window);
	}
}