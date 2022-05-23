// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : 3D_Normals.vs
// Description    : vertex shader used in 	DirLight, PointLight and Reflection programs
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//

#version 460 core

// vertex data interpretation 
layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoords;
layout (location = 2) in vec3 Normal;

//inputs
uniform mat4 PVM;
uniform mat4 Model;

// outputs to fragment shader
out vec2 FragTexCoords;
out vec3 FragNormal;
out vec3 FragPos;

void main()
{
	// calculate the vertex position
	gl_Position = PVM * vec4(Position, 1.0f);

	// pass through the vertex information
	FragTexCoords = TexCoords;
	FragNormal = mat3(transpose(inverse(Model))) * Normal;
	FragPos = vec3(Model * vec4(Position, 1.0f));
}