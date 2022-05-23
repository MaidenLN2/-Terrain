// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : 
// Description    : 
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//
#pragma once
#include <glew.h>
#include <glfw3.h>
#include "ShaderLoader.h"
#include <stb_image.h> 
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
#include "camera.h"

class Skybox
{
public:
	Skybox(std::map<std::string, GLuint>& ShaderMap, camera* Camera);
	~Skybox();
	void ImageLoad();
	GLuint GetTextureID();
	void Update(float Deltatime);
	void Render();

private:
	GLuint VAO;
	camera* Camera;
	GLuint TextureID;

	// object matrices and components (global variables)
	glm::mat4 ModelMat;

	glm::mat4 PVMMat;

	GLuint Program_Cubemap;

};