#include "Camera.h"
#include <iostream>






Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch ) : 
Front(glm::vec3(0.0,0.0,-1.0f)),
movementSpeed(SPEED),
mouseSens(SENS),
zoom(ZOOM)
{
	Position = position;
	Pitch = pitch;
	Yaw = yaw;
	WorldUp = up;
	UpdateCameraVectors();

}



Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
	Front(glm::vec3(0.0, 0.0, -1.0)),
	movementSpeed(SPEED),
	mouseSens(SENS),
	zoom(ZOOM)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	
	UpdateCameraVectors();
}



Camera::~Camera() {
	std::cout << "CAMERA DESTRUCTOR CALLED" << std::endl;
}


glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(Position, Position + Front, Up);
}



void Camera::ProcessKeyboardInput (Camera_Movement direction, float deltaTime) {
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD) {
		Position += Front * velocity;
	}
	if (direction == BACKWARD) {
		Position -= Front * velocity;
	}
	if (direction == RIGHT) {
		Position += Right * velocity;
	}
	if (direction == LEFT) {
		Position -= Right * velocity;
	}
	//Position.y = 0.0f; //--Toggle Fly cam
}



void Camera::ProcessMouseMovement(float offsetX, float offsetY, GLboolean constraintPitch) {
	offsetX *= mouseSens;
	offsetY *= mouseSens;
	Yaw += offsetX;
	Pitch += offsetY;

	if (constraintPitch) {
		if (Pitch > 89.0f) {
			Pitch = 89.0f;
		}
		if (Pitch < -89.0f) {
			Pitch = -89.0f;
		}
	}
	
	//update camera vecs
	UpdateCameraVectors();

}



void Camera::processMouseScroll(float yoffset) {
	zoom -= (float)yoffset;
	if (zoom < 1.0f) {
		zoom = 1.0f;
	}
	if (zoom > 60.0f) {
		zoom = 60.0f;
	}

}



void Camera::UpdateCameraVectors () {
	glm::vec3 front; //stores the new front vector
	//creates a direction vector 
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

	Front = glm::normalize(front);
	std::cout << "UPDATING CAMERA VECS New Front: " << Front.x << Front.y << Front.z << '\n';

	//re calculate the Right and the Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}