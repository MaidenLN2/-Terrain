// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : SkyBox.vs
// Description    : vertex shader used in Skybox program
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//

#version 460 core

// vertex data interpretation
layout (location = 0) in vec3 Position;

// inputs
uniform mat4 PVMMat;

// outputs to fragment sgader
out vec3 FragTexCoords;

void main()
{
	gl_Position = PVMMat * vec4(Position, 1.0f);
	FragTexCoords =  Position;
}