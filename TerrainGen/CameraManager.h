#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include <Camera.h>

class CameraManager {
public:
	static CameraManager* getInstance();
	Camera* getCamera();

private:
	CameraManager();
	static CameraManager* m_cameraManager;
	Camera* m_camera;
};

#endif //CAMERA_MANAGER_H