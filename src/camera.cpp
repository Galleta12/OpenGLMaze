#include "Camera.h"
#include <iostream>
#include "Vector3D.h"
#include "RadToDegree.h"
#include "Point.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	// glm::mat4 view = glm::mat4(1.0f);
	// glm::mat4 projection = glm::mat4(1.0f);

	// // Makes camera look in the right direction from the right position
	// view = glm::lookAt(Position, Position + Orientation, Up);
	// // Adds perspective to the scene
	// projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);
	
	
	Vector3D currentPos(Position.x,Position.y,Position.z);

	Point eye(currentPos.x,currentPos.y,currentPos.z);

	Vector3D center = currentPos + Vector3D(Orientation.x,Orientation.y,Orientation.z);



	mViewMatrix->look(eye,center,Vector3D::UP());

	mProjectionMatrix->setPerspective(RadToDegree::ToRadians(FOVdeg), (float)width / height, nearPlane, farPlane);


	// viewMatrix = view;
	// cameraMatrix = projection ;





}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	
	// glUniformMatrix4fv(glGetUniformLocation(shader.ID, "u_view_matrix"), 1,  GL_FALSE, glm::value_ptr(viewMatrix));
	// glUniformMatrix4fv(glGetUniformLocation(shader.ID, "u_projection_matrix"), 1,   GL_FALSE, glm::value_ptr(cameraMatrix));
	

	// shader.set_view_matrixGLM(viewMatrix);
	// shader.set_Projection_matrixGLM(cameraMatrix);
	shader.set_view_matrix(mViewMatrix->getMatrix());
	shader.set_projection_matrix(mProjectionMatrix->getMatrix());


}



void Camera::Inputs(GLFWwindow* window, float deltaTime)
{
	 // Adjust speed based on delta time (for smoother movement)
    float adjustedSpeed = speed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Position += adjustedSpeed * Orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Position += adjustedSpeed * -glm::normalize(glm::cross(Orientation, Up));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Position += adjustedSpeed * -Orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Position += adjustedSpeed * glm::normalize(glm::cross(Orientation, Up));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        Position += adjustedSpeed * Up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        Position += adjustedSpeed * -Up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        speed = 0.4f;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        speed = 0.1f;
    }


	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		Vector3D newCross = Vector3D::Cross(Vector3D(Orientation.x,Orientation.y,Orientation.z),Vector3D::UP()).normalize();
		
		Vector3D mynewOrientation = Vector3D::Rotation(Vector3D(Orientation.x,Orientation.y,Orientation.z), newCross, RadToDegree::ToRadians(-rotX) );

		

		// std::cout<< "new Orientation glm: " << glm::to_string(newOrientation)<<std::endl;
		
		// std::cout<< " myyy: " << mynewOrientation<<std::endl;
		
		// Decides whether or not the next vertical Orientation is legal or not
		
		// if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		// {
		// 	Orientation = newOrientation;
		// }
		
		if (abs(Vector3D::AngleInRad(mynewOrientation,Vector3D::UP()) - RadToDegree::ToRadians(90.0f)) <= RadToDegree::ToRadians(85.0f))
		{
			Orientation.x = mynewOrientation.x;
			Orientation.y = mynewOrientation.y;
			Orientation.z = mynewOrientation.z;
		}
		
		// Rotates the Orientation left and right
		//Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
		
		
		Vector3D CurrentOrientation = Vector3D::Rotation(Vector3D(Orientation.x,Orientation.y,Orientation.z),Vector3D::UP(),RadToDegree::ToRadians(-rotY));


		Orientation.x = CurrentOrientation.x;
		Orientation.y = CurrentOrientation.y;
		Orientation.z = CurrentOrientation.z;

		
		//std::cout<< "Orientation glm: " << glm::to_string(Orientation)<<std::endl;


		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}