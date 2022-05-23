//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : ShaderLoader.h
// Description    : class file for shader loader
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//

#pragma once

// Library Includes
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <map>

class ShaderLoader
{

public:
	static GLuint CreateProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename, std::map<std::string, GLuint>& ShaderMap);

private:
	ShaderLoader(void);
	~ShaderLoader(void);
	static GLuint CreateShader(GLenum shaderType, const char* shaderName, std::map<std::string, GLuint>& ShaderMap);
	static std::string ReadShaderFile(const char* filename);
	static void PrintErrorDetails(bool isShader, GLuint id, const char* name);
};
