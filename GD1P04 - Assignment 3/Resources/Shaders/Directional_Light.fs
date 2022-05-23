// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : Directional_Light.fs
// Description    : fragment shader used in DirLight program
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
#version 460 core

// creating struct
struct DirectionalLight
{
    vec3 Direction;
    vec3 Color;
    float AmbientStrength;
    float LightSpecularStrength;
};

// vertex shader input
in vec2 FragTexCoords;
in vec3 FragNormal;
in vec3 FragPos;

// uniform inputs
uniform sampler2D ImageTexture0;
uniform vec3 CameraPos;
uniform float Shininess = 32.0f;
uniform DirectionalLight DirLight;

//output
out vec4 FinalColor;

// calculate light function
vec3 CalculateLight_Directional(DirectionalLight OneDirLight)
{
    // light direction
    vec3 Normal = normalize(FragNormal);

    // ambient component
    vec3 Ambient = OneDirLight.AmbientStrength  * OneDirLight.Color;

    // diffuse component 
    float DiffuseStrength = max(dot(Normal, -OneDirLight.Direction), 0.0f);
    vec3 Diffuse = DiffuseStrength * OneDirLight.Color;

    // specular component
    vec3 ReverseViewDir = normalize(CameraPos - FragPos); 
    vec3 HalfwayVector = normalize(-OneDirLight.Direction + ReverseViewDir); // Blinn-Phong
    float SpecularReflectivity = pow(max(dot(Normal, HalfwayVector), 0.0f), Shininess);
    vec3 Specular = OneDirLight.LightSpecularStrength * SpecularReflectivity * OneDirLight.Color;

    // combine the lighting components
    vec3 Light = vec3(Ambient + Diffuse + Specular);
    
    return Light;
}

void main()
{
    // calculate each of the DirectionalLight lights and add the results
    vec3 LightOutput = vec3(0.0f, 0.0f, 0.0f);

    LightOutput += CalculateLight_Directional(DirLight); 

    //calculate the final color
    FinalColor = vec4(LightOutput, 1.0f) * texture(ImageTexture0, FragTexCoords);
}