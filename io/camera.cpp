#include "camera.h";
using namespace glm;

Camera::Camera(vec3 position) 
	: cameraPos(position),
	worldUp(vec3(0.0f, 1.0f, 0.0f)), 
	yaw(-90.0f), 
	pitch(0.0f), 
	speed(2.5f), 
	zoom(4.5f), 
	cameraFront(vec3(0.0f, 0.0f, -1.0f)) {
	updateCameraVectors();
}


void Camera::updateCameraDirection(double dx, double dy){
	yaw += dx;
	pitch += dy;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	else if (pitch < -89.0f) {
		pitch = -89.0f;
	}
	updateCameraVectors();
}
void Camera::updateCameraPosition(CameraDirection dir, double dt) {
	float velocity = (float)dt * speed;
	switch (dir) {
	case CameraDirection::FORWARD:
		cameraPos += cameraFront * velocity;
		break;
	case CameraDirection::BACKWARD:
		cameraPos -= cameraFront * velocity;
		break;
	case CameraDirection::RIGHT:
		cameraPos += cameraRight * velocity;
		break;
	case CameraDirection::LEFT:
		cameraPos -= cameraRight * velocity;
		break;
	case CameraDirection::UP:
		cameraPos += cameraUp * velocity;
		break;
	case CameraDirection::DOWN:
		cameraPos -= cameraUp * velocity;
		break;
	}

	
}
void Camera::updateCameraZoom(double dy) { 
	if (zoom >= 1.0f && zoom <= 45.0f) {
		zoom -= dy;
	}
	else if (zoom < 1.0f) {
		zoom = 1.0f;
	}
	else {
		zoom = 45.0f;
	}
}

float Camera::getZoom() {
	return zoom;
}

mat4 Camera::getViewMatrix(){
	return lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::updateCameraVectors() {
	vec3 direction;
	direction.x = cos(radians(yaw)) * cos(radians(pitch));
	direction.y = sin(radians(pitch));
	direction.z = sin(radians(yaw)) * cos(radians(pitch));
	cameraFront = normalize(direction);
	cameraRight = normalize(cross(cameraFront, worldUp));
	cameraUp = normalize(cross(cameraFront, cameraRight));

}