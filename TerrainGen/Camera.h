#ifndef CAMERA_H
#define CAMERA_H

#include <opengl.h>

class Camera
{
public:
	Camera();
	
	glm::mat4 getViewMatrix();

	void rotateCamera(GLfloat xoffset, GLfloat yoffset);

private:
	void updateCameraVectors();

	glm::vec3 m_position;
	glm::vec3 m_target;
	glm::vec3 m_direction;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	GLfloat m_yaw;
	GLfloat m_pitch;
};

#endif //CAMERA_H 