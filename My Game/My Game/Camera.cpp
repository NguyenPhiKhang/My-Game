#include "Camera.h"

Camera::Camera()
{
	XCamera = YCamera = 0;
}

Camera::~Camera()
{
}

void Camera::setPositionCam(float x, float y)
{
	this->XCamera = x;
	this->YCamera = y;
}

void Camera::setBoundary(float bLeft, float bRight)
{
	boundaryLeft = bLeft;
	boundaryRight = bRight;
}

D3DXVECTOR2 Camera::CameraTransform(float xWorld, float yWorld)
{
	return D3DXVECTOR2(xWorld-XCamera, yWorld-YCamera);
}
