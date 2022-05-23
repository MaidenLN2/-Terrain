// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : LightManager.cpp
// Description    : light manager for directional and point lights
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//

#include "LightManager.h"

LightManager::LightManager()
{
	// light source arrays
	PointLights[0].Position = glm::vec3(-4.0f, 4.0f, 5.0f);
	PointLights[0].Color = glm::vec3(0.0f, 1.0f, 0.0f);
	PointLights[0].AmbientStrength = 0.03f;
	PointLights[0].LightSpecularStrength = 1.0f;
	PointLights[0].AttenuationConstant = 1.0f;
	PointLights[0].AttenuationLinear = 0.045f;
	PointLights[0].AttenuationExponent = 0.0075f;

	PointLights[1].Position = glm::vec3(4.0f, -4.0f, 5.0f);
	PointLights[1].Color = glm::vec3(1.0f, 0.0f, 0.0f);
	PointLights[1].AmbientStrength = 0.03f;
	PointLights[1].LightSpecularStrength = 1.0f;
	PointLights[1].AttenuationConstant = 1.0f;
	PointLights[1].AttenuationLinear = 0.022f;
	PointLights[1].AttenuationExponent = 0.0019f;

	// directional light
	DirLight.Direction = glm::vec3(-1.0f, -1.0f, 0.0f);
	DirLight.Color = glm::vec3(1.0f, 1.0f, 1.0f);
	DirLight.AmbientStrength = 0.02f;
	DirLight.LightSpecularStrength = 1.0f;

}

LightManager::~LightManager()
{
}

void LightManager::Render(GLuint program)
{	
	glUniform1f(glGetUniformLocation(program, "Shininess"), Shininess);

	// accessed point lights (first)
	glUniform3fv(glGetUniformLocation(program, "PointLights[0].Position"), 1, glm::value_ptr(PointLights[0].Position));
	glUniform3fv(glGetUniformLocation(program, "PointLights[0].Color"), 1, glm::value_ptr(PointLights[0].Color));
	glUniform1f(glGetUniformLocation(program, "PointLights[0].AmbientStrength"), PointLights[0].AmbientStrength);
	glUniform1f(glGetUniformLocation(program, "PointLights[0].LightSpecularStrength"), PointLights[0].LightSpecularStrength);
	glUniform1f(glGetUniformLocation(program, "PointLights[0].AttenuationConstant"), PointLights[0].AttenuationConstant);
	glUniform1f(glGetUniformLocation(program, "PointLights[0].AttenuationLinear"), PointLights[0].AttenuationLinear);
	glUniform1f(glGetUniformLocation(program, "PointLights[0].AttenuationExponent"), PointLights[0].AttenuationExponent);

	// accessed point lights (second)
	glUniform3fv(glGetUniformLocation(program, "PointLights[1].Position"), 1, glm::value_ptr(PointLights[1].Position));
	glUniform3fv(glGetUniformLocation(program, "PointLights[1].Color"), 1, glm::value_ptr(PointLights[1].Color));
	glUniform1f(glGetUniformLocation(program, "PointLights[1].AmbientStrength"), PointLights[1].AmbientStrength);
	glUniform1f(glGetUniformLocation(program, "PointLights[1].LightSpecularStrength"), PointLights[1].LightSpecularStrength);
	glUniform1f(glGetUniformLocation(program, "PointLights[1].AttenuationConstant"), PointLights[1].AttenuationConstant);
	glUniform1f(glGetUniformLocation(program, "PointLights[1].AttenuationLinear"), PointLights[1].AttenuationLinear);
	glUniform1f(glGetUniformLocation(program, "PointLights[1].AttenuationExponent"), PointLights[1].AttenuationExponent);

	// accessed directional lights
	glUniform3fv(glGetUniformLocation(program, "DirLight.Direction"), 1, glm::value_ptr(DirLight.Direction));
	glUniform3fv(glGetUniformLocation(program, "DirLight.Color"), 1, glm::value_ptr(DirLight.Color));
	glUniform1f(glGetUniformLocation(program, "DirLight.AmbientStrength"), DirLight.AmbientStrength);
	glUniform1f(glGetUniformLocation(program, "DirLightLightSpecularStrength"), DirLight.LightSpecularStrength);
}
