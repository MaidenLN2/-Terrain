// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : Terrain.h
// Description    : class file for terrain object
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//

#pragma once

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

class Terrain
{
public:
	// terrain functions
	Terrain(GLuint TextureID, GLuint ProgramID);
	~Terrain();
	void SetPosition(glm::vec3 position);
	void Update(float DeltaTime, glm::mat4 CameraPV);
	void Render();
	void SetFaceCulling(bool faceculling);

private:
	GLuint VAO;

	// object matrices and components (global variables)
	glm::vec3 ObjPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	float ObjRotationAngle = 0.0f;
	glm::vec3 ObjScale = glm::vec3(0.5f, 0.5, 0.5f);
	glm::mat4 TranslationMat;
	glm::mat4 RotationMat;
	glm::mat4 ScaleMat;
	glm::mat4 ObjModelMat;
	glm::mat4 PVMMat;

	GLuint TextureID;
	GLuint ProgramID;

	int IndexCount;
	int DrawType;

	bool facecull = false;
};

