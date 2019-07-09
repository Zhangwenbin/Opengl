#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>

#include<glm\glm\gtc\matrix_transform.hpp>
#include<glm/glm/glm.hpp>
#include<glm\glm\gtc\type_ptr.hpp>

#include <functional>


// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.10f;
const float ZOOM = 45.0f;

class Camera
{
public:
	float Zoom = 45.0f;
	float aspect = 1.3f;
	float near = 0.1f;
	float far = 100.0f;

	glm::vec3 cameraPos = glm::vec3(10, 20, 30);
	glm::vec3 cameraUp = glm::vec3(0, 1, 0);
	glm::vec3 front = glm::vec3(0, 0, -1);
	glm::vec3 right = glm::vec3(1, 0, 0);
	glm::vec3 worldUp= glm::vec3(0, 1, 0);

	// Euler Angles
	float Yaw;
	float Pitch;

	float moveSpeed;
	float MouseSensitivity;

	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : front(glm::vec3(0.0f, 0.0f, -1.0f)), moveSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		cameraPos = position;
		worldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	// Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), moveSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		cameraPos = glm::vec3(posX, posY, posZ);
		worldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(cameraPos, cameraPos + front, cameraUp);
	}

	glm::mat4 GetProjectionMatrix()
	{
		return glm::perspective(glm::radians(Zoom), aspect, near, far);
	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = moveSpeed * deltaTime;
		if (direction == FORWARD)
			cameraPos += glm::vec3(front.x,0,front.z) * velocity;
		if (direction == BACKWARD)
			cameraPos -= glm::vec3(front.x, 0, front.z) * velocity;
		if (direction == LEFT)
			cameraPos -= glm::vec3(right.x, 0, right.z) * velocity;
		if (direction == RIGHT)
			cameraPos += glm::vec3(right.x, 0, right.z) * velocity;
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;
		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Euler angles
		updateCameraVectors();
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset)
	{
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yoffset;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}



private:	

	// Calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors()
	{
		// Calculate the new Front vector
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		cameraUp = glm::normalize(glm::cross( right,front ));
	}

	
	
};

#endif // CAMERA.H

