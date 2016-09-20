#include <vector>
#include <Camera.h>
#include <Debug.h>
#include <string>

Camera::Camera() {
	m_position = glm::vec3(0.0f, -4.0f, 1.0f);
	m_target = glm::vec3(0.0f, 0.0f, 0.0f);
	m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_yaw = 0.0f;
	m_pitch = 80.0f;
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(m_position, m_target, m_up);
}

void Camera::updateCameraVectors() {
	m_direction = m_position - m_target;
	m_right = glm::normalize(glm::cross(m_worldUp, glm::normalize(m_direction)));
	m_up = glm::normalize(glm::cross(m_direction, m_right));
}

void Camera::rotateCamera(GLfloat xoffset, GLfloat yoffset) {
	float y = m_yaw;
	float p = m_pitch;
	m_yaw += xoffset * 0.1f;
	m_pitch += yoffset * 0.1f;
	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;
	m_position.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw)) * glm::length(m_direction);
	m_position.y = sin(glm::radians(m_pitch)) * glm::length(m_direction);
	m_position.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw)) * glm::length(m_direction);
	updateCameraVectors();
}
