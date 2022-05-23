//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : ShaderLoader.cpp
// Description    : contains fuctions fo load shaders
// Author         : Lera Blokhina (not really but file looks more official this way)
// Mail           : valeriia.blokhina@mds.ac.nz
//

#include "ShaderLoader.h" 
#include<iostream>
#include<fstream>
#include<vector>

ShaderLoader::ShaderLoader(void) {}
ShaderLoader::~ShaderLoader(void) {}

GLuint ShaderLoader::CreateProgram(const char* vertexShaderFilename, const char* fragmentShaderFilename, std::map<std::string, GLuint>& ShaderMap)
{
	// Create the shaders from the filepath
	GLuint vertexShaderID = CreateShader(GL_VERTEX_SHADER, vertexShaderFilename, ShaderMap);
	GLuint fragmentShaderID = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderFilename, ShaderMap);


	// Create the program handle, attach the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShaderID);
	glAttachShader(program, fragmentShaderID);
	glLinkProgram(program);

	// Check for link errors
	int link_result = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE)
	{
		std::string programName = vertexShaderFilename + *fragmentShaderFilename;
		PrintErrorDetails(false, program, programName.c_str());
		return 0;
	}
	return program;
}

GLuint ShaderLoader::CreateShader(GLenum shaderType, const char* shaderName, std::map<std::string, GLuint>& ShaderMap)
{
	// Read the shader files and save the source code as strings
	std::string shaderSourceCode = ReadShaderFile(shaderName);

	// MAPPING HELL
	if (ShaderMap.find(shaderName) != ShaderMap.end())
	{
		std::cout << "Retrieving " << shaderName << " from the ShaderMap" << std::endl;

		return ShaderMap[shaderName];
	}
	else
	{
		// Create the shader ID and create pointers for source code string and length
		// GLuint shaderID = 0; big no, 0 is unassign ID
		GLuint shaderID = glCreateShader(shaderType);
		const char* shader_code_ptr = shaderSourceCode.c_str();
		const int shader_code_size = shaderSourceCode.length();

		// Populate the Shader Object (ID) and compile
		glShaderSource(shaderID, 1, &shader_code_ptr, &shader_code_size);
		glCompileShader(shaderID);


		// Check for errors
		int compile_result = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compile_result);
		if (compile_result == GL_FALSE)
		{
			PrintErrorDetails(true, shaderID, shaderName);
			return 0;
		}

		std::cout << "Adding " << shaderName << " from the ShaderMap" << std::endl;

		ShaderMap[shaderName] = shaderID;
		return shaderID; // return data	
	}

}

std::string ShaderLoader::ReadShaderFile(const char* filename)
{
	// Open the file for reading
	std::ifstream file(filename, std::ios::in);
	std::string shaderCode;

	// Ensure the file is open and readable
	if (!file.good()) {
		std::cout << "Cannot read file:  " << filename << std::endl;
		return "";
	}

	// Determine the size of of the file in characters and resize the string variable to accomodate
	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());

	// Set the position of the next character to be read back to the beginning
	file.seekg(0, std::ios::beg);
	// Extract the contents of the file and store in the string variable
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

void ShaderLoader::PrintErrorDetails(bool isShader, GLuint id, const char* name)
{
	int infoLogLength = 0;
	// Retrieve the length of characters needed to contain the info log
	(isShader == true) ? glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength) : glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> log(infoLogLength);

	// Retrieve the log info and populate log variable
	(isShader == true) ? glGetShaderInfoLog(id, infoLogLength, NULL, &log[0]) : glGetProgramInfoLog(id, infoLogLength, NULL, &log[0]);
	std::cout << "Error compiling " << ((isShader == true) ? "shader" : "program") << ": " << name << std::endl;
	std::cout << &log[0] << std::endl;
}
