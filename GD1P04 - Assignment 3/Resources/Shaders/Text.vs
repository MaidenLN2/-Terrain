//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2021 Media Design School
//
// File Name      : Text.vs
// Description    : shader for text
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//

#version 460 core

layout (location = 0) in vec4 Vertex; // (vec2:Position, vec2:TexCoords)

out vec2 FragTexCoords;

uniform mat4 ProjectionMat;

void main()
{
	gl_Position = ProjectionMat * vec4(Vertex.xy, 0.0f, 1.0f);
	FragTexCoords = Vertex.zw;
}