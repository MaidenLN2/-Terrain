// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : 
// Description    : 
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//
#include "Skybox.h"

Skybox::Skybox(std::map<std::string, GLuint> &ShaderMap, camera* Camera)
{
	// create the program
	Program_Cubemap = ShaderLoader::CreateProgram("Resources/Shaders/SkyBox.vs",
		"Resources/Shaders/SkyBox.fs",
		ShaderMap);
	TextureID = NULL;

	this->Camera = Camera;

	//creatingvertices and indices of VAO skybox
	GLfloat SkyboxVertices[] = {
		// index		// position              
		// front
		/* 00 */    -0.5f,  0.5f,  0.5f,    
		/* 01 */    -0.5f, -0.5f,  0.5f,   
		/* 02 */     0.5f, -0.5f,  0.5f,    
		/* 03 */     0.5f,  0.5f,  0.5f,    

		// back 
		/* 04 */     0.5f,  0.5f, -0.5f,   
		/* 05 */     0.5f, -0.5f, -0.5f,   
		/* 06 */    -0.5f, -0.5f, -0.5f,   
		/* 07 */    -0.5f,  0.5f, -0.5f,   

		// right
		/* 08 */     0.5f,  0.5f,  0.5f,   
		/* 09 */     0.5f, -0.5f,  0.5f,   
		/* 10 */     0.5f, -0.5f, -0.5f,   
		/* 11 */     0.5f,  0.5f, -0.5f,   

		// left
		/* 12 */    -0.5f,  0.5f, -0.5f,   
		/* 13 */    -0.5f, -0.5f, -0.5f,   
		/* 14 */    -0.5f, -0.5f,  0.5f,   
		/* 15 */    -0.5f,  0.5f,  0.5f,   

		// top
		/* 16 */    -0.5f,  0.5f, -0.5f,   
		/* 17 */    -0.5f,  0.5f,  0.5f,   
		/* 18 */     0.5f,  0.5f,  0.5f,   
		/* 19 */     0.5f,  0.5f, -0.5f,   

		// bottom
		/* 20 */    -0.5f, -0.5f,  0.5f,   
		/* 21 */    -0.5f, -0.5f, -0.5f,   
		/* 22 */     0.5f, -0.5f, -0.5f,   
		/* 23 */     0.5f, -0.5f,  0.5f,   
	};

	GLuint SkyboxIndices[] = {
		0, 2, 1,        // front triangle 1
		0, 3, 2,        // front triangle 2
		4, 6, 5,        // back triangle 1
		4, 7, 6,        // back triangle 2
		8, 10, 9,        // right triangle 1
		8, 11, 10,        // right triangle 2
		12, 14, 13,        // left triangle 1
		12, 15, 14,        // left triangle 2
		16, 18, 17,        // top triangle 1
		16, 19, 18,        // top triangle 2
		20, 22, 21,        // bottom triangle 1
		20, 23, 22,        // bottom triangle 2
	};

	GLuint EBO;
	GLuint VBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyboxVertices), SkyboxVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SkyboxIndices), SkyboxIndices, GL_STATIC_DRAW);

	// vertex information 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
}
void Skybox::ImageLoad()
{
	// create and bind new texture template
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID);

	std::string FilePath[6];
	FilePath[0] = "Right.jpg";
	FilePath[1] = "Left.jpg";
	FilePath[2] = "Up.jpg";
	FilePath[3] = "Down.jpg";
	FilePath[4] = "Back.jpg";
	FilePath[5] = "Front.jpg";

	// load image data
	int ImageWidth;
	int ImageHeight;
	int ImageComponent;
	stbi_set_flip_vertically_on_load(false);

	for (int i = 0; i < 6; i++)
	{
		std::string FullFilePath = "Resources/Textures/Cubemaps/MountainOutpost/" + FilePath[i];
		unsigned char* ImageData = stbi_load(FullFilePath.c_str(), &ImageWidth, &ImageHeight, &ImageComponent, 0);

		// checking number of components loaded image has (rgb or rgba)
		GLint LoadedComponent = (ImageComponent == 4) ? GL_RGBA : GL_RGB;

		// populating texture with image data
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			LoadedComponent, ImageWidth, ImageHeight, 0,
			LoadedComponent, GL_UNSIGNED_BYTE, ImageData);

		stbi_image_free(ImageData);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// generate mipmaps, free the memory and unbind the texture
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

GLuint Skybox::GetTextureID()
{
	return TextureID;
}

void Skybox::Update(float Deltatime)
{
	ModelMat = glm::scale(glm::mat4(), glm::vec3(2000.0f, 2000.0f, 2000.0f));
	PVMMat = Camera->GetMatrixPV() * ModelMat;
}

void Skybox::Render()
{
	glUseProgram(Program_Cubemap);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID);
	glUniform1i(glGetUniformLocation(Program_Cubemap, "Texture0"), 0);
	glUniformMatrix4fv(glGetUniformLocation(Program_Cubemap, "PVMMat"), 1, GL_FALSE, glm::value_ptr(PVMMat));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glUseProgram(0);

}

Skybox::~Skybox()
{

}


