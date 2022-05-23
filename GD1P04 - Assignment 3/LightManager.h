// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : LightManager.h
// Description    : class file for light manager, contains variables needed to be passed to the main.cpp
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#define MAX_POINT_LIGHTS 4

// creating struct for light manager
struct PointLight
{
	glm::vec3 Position;
	glm::vec3 Color;
	float AmbientStrength;
	float LightSpecularStrength;

	float AttenuationConstant;
	float AttenuationLinear;
	float AttenuationExponent;
};

// creating struct for directional lights
struct DirectionalLight
{
	glm::vec3 Direction;
	glm::vec3 Color;
	float AmbientStrength;
	float LightSpecularStrength;
};

class LightManager
{
public:
	LightManager();
	~LightManager();
	void Render(GLuint program);

private:
	PointLight PointLights[MAX_POINT_LIGHTS];
	DirectionalLight DirLight;
	float Shininess = 32.0f;
};

