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

#include "Terrain.h"

Terrain::Terrain(GLuint TextureID, GLuint ProgramID)
{    
    // creating terrain
    const int squareSize = 256 / 2;
    const int vertexAttribCount = 5;
    const int indexPerQuad = 6;	// Indices needed to create a quad

    // Create the vertex array to hold the correct number of elements
    const int vertexCount = vertexAttribCount * squareSize * squareSize;
    GLfloat verticesHeightMapQuad[vertexCount];

    int vertexElement = 0;
    float startPos = squareSize - 1;

    for (size_t i = 0; i < squareSize; i++)
    {
        for (size_t j = 0; j < squareSize; j++)
        {
            float x = (-startPos + (2.0f * j));
            float z = (-startPos + (2.0f * i));

            // X
            verticesHeightMapQuad[vertexElement++] = x;

            // Y = 0
            verticesHeightMapQuad[vertexElement++] = 0;

            // Z
            verticesHeightMapQuad[vertexElement++] = z;

            // TexCoords.x
            verticesHeightMapQuad[vertexElement++] = (j / startPos);

            // TexCoords.y
            verticesHeightMapQuad[vertexElement++] = ((startPos - i) / startPos);
        }
    }

    const int indexCount = indexPerQuad * squareSize * squareSize;
    GLuint indicesHeightMapQuad[indexCount];

    int Element = 0;
    for (size_t i = 0; i < (squareSize - 1); i++)
    {
        for (size_t j = 0; j < (squareSize - 1); j++)
        {
            // First triangle of the quad
            indicesHeightMapQuad[Element++] = ((i * squareSize) + j);
            indicesHeightMapQuad[Element++] = (((i + 1) * squareSize) + j);
            indicesHeightMapQuad[Element++] = (((i + 1) * squareSize) + (j + 1));

            // Second triangle of the quad
            indicesHeightMapQuad[Element++] = ((i * squareSize) + j);
            indicesHeightMapQuad[Element++] = (((i + 1) * squareSize) + (j + 1));
            indicesHeightMapQuad[Element++] = ((i * squareSize) + (j + 1));
        }
    }

    // Create the Vertex Array and associated buffers
    GLuint VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat), verticesHeightMapQuad, GL_STATIC_DRAW);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indicesHeightMapQuad, GL_STATIC_DRAW);

    // Vertex Information (Position, Texture Coords and Normals)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    this->IndexCount = indexCount;
    DrawType = GL_TRIANGLES;

    // storing textures and programs
    this->ProgramID = ProgramID;
    this->TextureID = TextureID;
}

Terrain::~Terrain()
{
}

void Terrain::SetPosition(glm::vec3 position)
{
    ObjPosition = position;
}

void Terrain::Update(float DeltaTime, glm::mat4 CameraPV)
{
    // calculate the translation matrix
    TranslationMat = glm::translate(glm::mat4(), ObjPosition);

    //if (ObjRotationAngle > 360.0f)
    //{
    //    ObjRotationAngle -= 360.0f;
    //}

    //ObjRotationAngle += 0.5f;

    // calculate the rotation matrix
    RotationMat = glm::rotate(glm::mat4(), glm::radians(ObjRotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));

    // calculate the scale matrix
    ScaleMat = glm::scale(glm::mat4(), ObjScale);

    // create object model matrix
    ObjModelMat = TranslationMat * RotationMat * ScaleMat;

    // calcualting PV camera
    PVMMat = CameraPV * ObjModelMat;
}

void Terrain::Render()
{
    glUseProgram(ProgramID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureID);
    glUniform1i(glGetUniformLocation(ProgramID, "ImageTexture0"), 0);

    GLint ModelMatLoc = glGetUniformLocation(ProgramID, "Model");
    glUniformMatrix4fv(ModelMatLoc, 1, GL_FALSE, glm::value_ptr(ObjModelMat));
    GLint PVMMatLoc = glGetUniformLocation(ProgramID, "PVM");
    glUniformMatrix4fv(PVMMatLoc, 1, GL_FALSE, glm::value_ptr(PVMMat));

    if (facecull == true)
    {
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);	// face culling
    }
    glBindVertexArray(VAO);
    glDrawElements(DrawType, IndexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    if (facecull == true)
    {
        glDisable(GL_CULL_FACE);
    }

    glUseProgram(0);
}

void Terrain::SetFaceCulling(bool faceculling)
{
    facecull = faceculling;
}
