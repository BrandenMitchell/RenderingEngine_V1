#pragma once
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//direction enums
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


// default values for camera 
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 4.5f;
const float SENS = 0.1f;
const float ZOOM = 45.0f;



class Camera {

private:
	


	
public: 
	//camera vectors (used to build view and pos matrix)
	glm::vec3 Position; //This is cameras position in world space, we tranform the world about this position
	glm::vec3 Front;	//this is a direction vector
	glm::vec3 Right;	//this is a right vector , the cameras right
	glm::vec3 Up;		//Cameras up vector, directly above camera
	glm::vec3 WorldUp;	//world up direction vector

	// euler angles
	float Yaw;
	float Pitch;
	//camera adjustments
	float mouseSens;
	float movementSpeed;
	float zoom;

	Camera(glm::vec3 position = glm::vec3(0.0, 0.0, 0.0), glm::vec3 up = glm::vec3(0.0, 1.0, 0.0),float yaw = YAW, float pitch = PITCH);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	~Camera();

	void UpdateCameraVectors(); 
	glm::mat4 GetViewMatrix();
	glm::vec3 GetPosition() { return Position; }
	void ProcessKeyboardInput (Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float offsetX, float offsetY, GLboolean constraintPitch = true);

	void processMouseScroll(float yoffset);
};

