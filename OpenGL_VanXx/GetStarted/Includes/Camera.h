#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw; // 绕Y轴旋转
	float Pitch; // 绕X轴旋转
	// 不考虑Roll 也就是绕Z轴旋转

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	glm::mat4 GetViewMatrix()
	{
		//return glm::lookAt(Position, Position + Front, Up);
		//glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 target = Position + Front;
		//glm::vec3 dir = glm::normalize(target - Position);
		//glm::vec3 dir = glm::normalize(Position - target);
		glm::vec3 dir = glm::normalize(Position - target);
		glm::vec3 fUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 right = glm::normalize(glm::cross(fUp, dir));
		glm::vec3 up = glm::normalize(glm::cross(dir, right));
		glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
		translation[3][0] = -Position.x;
		translation[3][1] = -Position.y;
		translation[3][2] = -Position.z;
		glm::mat4 rotation = glm::mat4(1.0f);
		rotation[0][0] = right.x; // First column, first row
		rotation[1][0] = right.y;
		rotation[2][0] = right.z;
		rotation[0][1] = up.x; // First column, second row
		rotation[1][1] = up.y;
		rotation[2][1] = up.z;
		rotation[0][2] = dir.x; // First column, third row
		rotation[1][2] = dir.y;
		rotation[2][2] = dir.z;

		return rotation * translation; // 反过来还不行，肯定是先确定位置再计算轴；反过来就是先计算了轴再位移

		//glm::vec3 position = Position;
		////glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
		//glm::vec3 target = Position + Front;
		//glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		//// 1. Position = known
		//// 2. Calculate cameraDirection
		//glm::vec3 zaxis = glm::normalize(position - target);
		//// 3. Get positive right axis vector
		//glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
		//// 4. Calculate camera up vector
		//glm::vec3 yaxis = glm::cross(zaxis, xaxis);

		//// Create translation and rotation matrix
		//// In glm we access elements as mat[col][row] due to column-major layout
		//glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
		//translation[3][0] = -position.x; // Third column, first row
		//translation[3][1] = -position.y;
		//translation[3][2] = -position.z;
		//glm::mat4 rotation = glm::mat4(1.0f);
		//rotation[0][0] = xaxis.x; // First column, first row
		//rotation[1][0] = xaxis.y;
		//rotation[2][0] = xaxis.z;
		//rotation[0][1] = yaxis.x; // First column, second row
		//rotation[1][1] = yaxis.y;
		//rotation[2][1] = yaxis.z;
		//rotation[0][2] = zaxis.x; // First column, third row
		//rotation[1][2] = zaxis.y;
		//rotation[2][2] = zaxis.z;

		//// Return lookAt matrix as combination of translation and rotation matrix
		//return rotation * translation; // Remember to read from right to left (first translation then rotation)
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = SPEED * deltaTime;
		if (direction == FORWARD)
			Position += Front * velocity;
		if (direction == BACKWARD)
			Position -= Front * velocity;
		if (direction == LEFT)
			Position -= Right * velocity;
		if (direction == RIGHT)
			Position += Right * velocity;
	}

	void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true)
	{
		xOffset *= MouseSensitivity;
		yOffset *= MouseSensitivity;

		Yaw += xOffset;
		Pitch += yOffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void ProcessMouseScroll(float yOffset)
	{
		Zoom -= yOffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}
private:
	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);

		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};

#endif // !CAMERA_H
