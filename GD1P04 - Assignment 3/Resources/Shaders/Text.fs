//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2021 Media Design School
//
// File Name      : Text.fs
// Description    : shader for text
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//

#version 460 core

in vec2 FragTexCoords;

uniform sampler2D TextTexture;
uniform vec3 TextColor;

out vec4 FinalColor;

void main()
{
	float Alpha = texture(TextTexture, FragTexCoords).r;
	FinalColor = vec4(TextColor, Alpha);
}