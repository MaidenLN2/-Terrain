// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : SkyBox.fs
// Description    : fragment shader used in Skybox program
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//

#version 460 core
// vertex shader inputs
in vec3 FragTexCoords;

//uniform inputs
uniform samplerCube Texture0;

// output 
out vec4 FinalColor;

void main()
{
    FinalColor = texture(Texture0,FragTexCoords);
}