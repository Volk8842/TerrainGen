#include <CameraManager.h>

CameraManager* CameraManager::m_cameraManager = nullptr;

CameraManager* CameraManager::getInstance() {
	if (m_cameraManager == nullptr) {
		m_cameraManager = new CameraManager();
	}
	return m_cameraManager;
}

Camera* CameraManager::getCamera() {
	return m_camera;
}

CameraManager::CameraManager() {
	m_camera = new Camera();
}