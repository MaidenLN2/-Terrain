//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : camera.h
// Description    : class file for camera using matrices and freecam movement
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>
#include "Utilities.h"

class camera
{
public:
	camera(); //camera(
	~camera();
	glm::mat4 GetMatrixPV();
	void CalculateMatrixPV();
	glm::vec3 GetPosition();

	glm::mat4 ViewMat;
	glm::mat4 ProjectionMat;
	glm::mat4 PVMMat;

	// freecam variables
	//glm::vec3 Position; // similar to GetPosition() but separate to avoid effect on the rest of the code
	//glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f); // similar to CameraLookDir but separate to avoid effect on the rest of the code
	//glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f); // similar to CameraUpDir but separate to avoid effect on the rest of the code

	//float speed = 0.1f;
	float sensitivity = 100.0f;
	bool firstClick = true;
	void Update(GLFWwindow* Window, float DeltaTime);

private:

	// camera variables
	glm::vec3 CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 CameraLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 CameraTargetPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 CameraUpDir = glm::vec3(0.0f, 1.0f, 0.0f);
};
