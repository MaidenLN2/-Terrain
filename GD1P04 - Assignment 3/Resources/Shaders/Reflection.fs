// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : Reflection.fs
// Description    : fragment shader used in Reflection program
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//

#version 460 core

in vec3 FragNormal;
in vec3 FragPos;

//uniform inputs
uniform samplerCube Texture0;
uniform vec3 CameraPos;

// output 
out vec4 FinalColor;

void main()
{
    vec3 Normal =  normalize(FragNormal);
    vec3 ViewDir = normalize(FragPos - CameraPos);
    vec3 ReflectDir = reflect(ViewDir, Normal);
    FinalColor = texture(Texture0, ReflectDir);
}