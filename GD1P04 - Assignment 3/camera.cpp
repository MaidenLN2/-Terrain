//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name      : camera.cpp
// Description    : file containing functions for camera
// Author         : Lera Blokhina
// Mail           : valeriia.blokhina@mds.ac.nz
//

#include "camera.h"

camera::camera()
{

	// calculate orthographic projection matrix - anchor point (0, 0) at center
	ProjectionMat = glm::perspective(glm::radians(45.0f), (float)Utilities::WindowWidth / (float)Utilities::WindowHeight, 0.1f, 4000.0f);

	// calculate the view matrix from  camera variable
	ViewMat = glm::lookAt(CameraPos, (CameraPos + CameraLookDir), CameraUpDir);

	CalculateMatrixPV();
}

camera::~camera()
{
}

glm::mat4 camera::GetMatrixPV()
{
	return PVMMat;
}

void camera::CalculateMatrixPV()
{
	
	PVMMat = ProjectionMat * ViewMat;
}

glm::vec3 camera::GetPosition()
{
	return CameraPos;
}

void camera::Update(GLFWwindow* Window, float DeltaTime)
{
	// query GLFW key states (normalizing vectors)
		glm::vec3 normalmovevector;

		if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
		{
			//normalmovevector += glm::vec3(0.0f, 0.0f, 1.0f);
			normalmovevector += CameraLookDir;
		}
		if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
		{
			//normalmovevector += glm::vec3(0.0f, 0.0f, -1.0f);
			normalmovevector += -CameraLookDir;
		}
		if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
		{
			//normalmovevector += glm::vec3(-1.0f, 0.0f, 0.0f);
			normalmovevector += -glm::normalize(glm::cross(CameraLookDir, CameraUpDir));
		}
		if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
		{
			//normalmovevector += glm::vec3(1.0f, 0.0f, 0.0f);
			normalmovevector += glm::normalize(glm::cross(CameraLookDir, CameraUpDir));
		}
		if (glfwGetKey(Window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			//normalmovevector += glm::vec3(0.0f, 1.0f, 0.0f);
			normalmovevector += CameraUpDir;
		}
		if (glfwGetKey(Window, GLFW_KEY_E) == GLFW_PRESS)
		{
			//normalmovevector += glm::vec3(0.0f, -1.0f, 0.0f);
			normalmovevector += -CameraUpDir;
		}

		glm::normalize(normalmovevector);
		normalmovevector *= DeltaTime;
		CameraPos += normalmovevector;


		if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			//std::cout << "Mouse button left: press" << std::endl;
			glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			if (firstClick)
			{
				glfwGetCursorPos(Window, 0, 0);
				firstClick = false;
			}

			double Xpos;
			double Ypos;
			glfwGetCursorPos(Window, &Xpos, &Ypos);

			float rotX = sensitivity * (float)(Ypos - (Utilities::WindowHeight / 2)) / Utilities::WindowHeight;
			float rotY = sensitivity * (float)(Xpos - (Utilities::WindowHeight / 2)) / Utilities::WindowHeight;

			glm::vec3 newCameraLookDir = glm::rotate(CameraLookDir, glm::radians(-rotX), glm::normalize(glm::cross(CameraLookDir, CameraUpDir)));
			if (!((glm::angle(newCameraLookDir, CameraUpDir) <= glm::radians(5.0f) || (glm::angle(newCameraLookDir, -CameraUpDir) <= glm::radians(5.0f)))))
			{
				CameraLookDir = newCameraLookDir;
			}

			CameraLookDir = glm::rotate(CameraLookDir, glm::radians(-rotY), CameraUpDir);

			glfwSetCursorPos(Window, (Utilities::WindowWidth / 2), (Utilities::WindowHeight / 2));
		}
		else if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{			
			glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstClick = true;
		}

		ViewMat = glm::lookAt(CameraPos, (CameraPos + CameraLookDir), CameraUpDir);

		CalculateMatrixPV();
}

