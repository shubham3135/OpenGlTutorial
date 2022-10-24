#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

enum class CameraDirection {
	NONE = 0,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera {
public:
	vec3 cameraPos;
	vec3 cameraFront;
	vec3 cameraUp;
	vec3 cameraRight;

	vec3 worldUp;

	float yaw;
	float pitch;
	float speed;
	float zoom;

	Camera(vec3 position);

	void updateCameraDirection(double dx, double dy);
	void updateCameraPosition(CameraDirection dir, double dt);
	void updateCameraZoom(double dy);

	mat4 getViewMatrix();

private:
	void updateCameraVectors();


};


#endif // !CAMERA_H

