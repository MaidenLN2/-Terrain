// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : 3DLight_Phong.fs
// Description    : fragment shader used in PointLight program
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//

#version 460 core
#define  MAX_POINT_LIGHTS 2

// creating struct for light manager
struct PointLight
{
    vec3 Position;
    vec3 Color;
    float AmbientStrength;
    float LightSpecularStrength;

    float AttenuationConstant;
    float AttenuationLinear;
    float AttenuationExponent;
};

// vertex shader input
in vec2 FragTexCoords;
in vec3 FragNormal;
in vec3 FragPos;

// uniform inputs
uniform sampler2D ImageTexture0;
uniform vec3 CameraPos;
//uniform float AmbientStrength	    = 0.05f;
//uniform vec3 AmbientColor		    = vec3(1.0f, 1.0f, 1.0f);
// vec3 LightColor			    = vec3(1.0f, 1.0f, 1.0f);
//uniform vec3 LightPos			    = vec3(-2.0f, 6.0f, 3.0f);
//uniform float LightSpecularStrength = 1.0f;
uniform float Shininess = 32.0f;
//uniform float RimExponent			= 4.0f;
//uniform vec3 RimColor				= vec3(1.0f, 0.0f, 0.0f);
uniform PointLight PointLights[MAX_POINT_LIGHTS];

//output
out vec4 FinalColor;

// calculate light function
vec3 CalculateLight_Point(PointLight OnePointLight)
{
    // light direction
    vec3 Normal = normalize(FragNormal);
    vec3 LightDir = normalize(FragPos - OnePointLight.Position);

    // ambient component
    vec3 Ambient = OnePointLight.AmbientStrength  * OnePointLight.Color;

    // diffuse component 
    float DiffuseStrength = max(dot(Normal, -LightDir), 0.0f);
    vec3 Diffuse = DiffuseStrength * OnePointLight.Color;

    // specular component
    vec3 ReverseViewDir = normalize(CameraPos - FragPos); 
    //vec3 ReflectedDir = reflect(LightDir, Normal); // simple Phong
    vec3 HalfwayVector = normalize(-LightDir + ReverseViewDir); // Blinn-Phong
    float SpecularReflectivity = pow(max(dot(Normal, HalfwayVector), 0.0f), Shininess);
    //float SpecularReflectivity = pow(max(dot(ReverseViewDir, ReflectedDir), 0.0f), Shininess); // simple Phong
    vec3 Specular = OnePointLight.LightSpecularStrength * SpecularReflectivity * OnePointLight.Color;

    // rim component 
    //float RimFactor = 1.0f - dot(Normal, ReverseViewDir);
    //RimFactor = smoothstep(0.0f, 1.0f, RimFactor);
    //RimFactor = pow(RimFactor, RimExponent);
    //vec3 Rim = RimFactor * RimColor * LightColor;

    // combine the lighting components
    vec3 Light = vec3(Ambient + Diffuse + Specular);

    // calculate and apply attenuation 
    float Distance = length(OnePointLight.Position - FragPos);
    float Attenuation = OnePointLight.AttenuationConstant + (OnePointLight.AttenuationLinear * Distance) + (OnePointLight.AttenuationExponent * pow(Distance, 2));
    Light /= Attenuation;
    
    return Light;
}

void main()
{
    // calculate each of the point lights and add the results
    vec3 LightOutput = vec3(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        LightOutput += CalculateLight_Point(PointLights[i]); // light_point? 
    }

    //calculate the final color
    FinalColor = vec4(LightOutput, 1.0f) * texture(ImageTexture0, FragTexCoords);
}