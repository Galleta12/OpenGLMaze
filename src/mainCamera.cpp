#include "MainCamera.h"


MainCamera::MainCamera(Manager &mManager)
:Entity(mManager)
{

    Entity::addComponent<CameraComponent>(Vector3D(0.0f, 0.0f, 2.0f));
    //needs to be on this group
    Entity::addGroup(Game::groupCameras);
    saveComponents();
}

MainCamera::~MainCamera()
{
    

}

void MainCamera::update(float deltaTime)
{
    Entity::update(deltaTime);
    //for this type of movement we want to use the look to constantly
    //look to the  place where the mouse is facing

    Inputs(deltaTime);
    RotationCamera(deltaTime);
    ApplyNewPosition(deltaTime);

}


void MainCamera::draw(Shader &shader)
{
    Entity::draw(shader);

};


void MainCamera::saveComponents()
{
    mCameraComponent = &Entity::getComponent<CameraComponent>();
    //we want to draw at the beginning
    mCameraComponent->shouldDraw = true;

    Vector3D initialCenter = mCameraComponent->eyePosition + mCameraComponent->orientation;
    
    mCameraComponent->setLooKViewCamera(mCameraComponent->eyePosition,initialCenter,Vector3D::UP());
    //for the shaders they are done on the draw using this data

    //for now the aspct ration is
    float aspect =  static_cast<float>(Game::Width / Game::Height);
    
    
    
    
    
    mCameraComponent->setPerspectiveProjection(RadToDegree::ToRadians(45.0f),aspect, 0.1f,100.0f);



}


void MainCamera::ZoomCamera(float deltaTime)
{
}

void MainCamera::ApplyNewPosition(float deltaTime)
{

    Vector3D newCenter = mCameraComponent->eyePosition + mCameraComponent->orientation;
    mCameraComponent->setLooKViewCamera(mCameraComponent->eyePosition,newCenter,Vector3D::UP());
    float aspect =  static_cast<float>(Game::Width / Game::Height);
    
    //mCameraComponent->setPerspectiveProjection(RadToDegree::ToRadians(45.0f),aspect, 0.1f,100.0f);
    mCameraComponent->setPerspectiveProjection(RadToDegree::ToRadians(90.0f),aspect, 0.1f,100.0f);

}

void MainCamera::Inputs(float deltaTime)
{



     // Adjust speed based on delta time (for smoother movement)
    float adjustedSpeed = cameraSpeed * deltaTime;

    if (glfwGetKey(Game::window, GLFW_KEY_W) == GLFW_PRESS)
    {
        mCameraComponent->eyePosition +=  mCameraComponent->orientation * adjustedSpeed;

    }
    if (glfwGetKey(Game::window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Vector3D righOrientation = Vector3D::Cross(mCameraComponent->orientation,Vector3D::UP());
        //we want to get the inverse
        righOrientation.x *= -1.0f;
        righOrientation.y *= -1.0f;
        righOrientation.z *= -1.0f;
        righOrientation.normalize();
        
        mCameraComponent->eyePosition +=  righOrientation * adjustedSpeed;
    
    }
    if (glfwGetKey(Game::window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Vector3D inverOrientation(mCameraComponent->orientation.x,mCameraComponent->orientation.y,mCameraComponent->orientation.z);

        inverOrientation.x *= -1.0f;
        inverOrientation.y *= -1.0f;
        inverOrientation.z *= -1.0f;
        
        mCameraComponent->eyePosition += inverOrientation * adjustedSpeed;
    }
    if (glfwGetKey(Game::window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Vector3D righOrientation = Vector3D::Cross(mCameraComponent->orientation,Vector3D::UP());
        //we want to get the inverse
        
        righOrientation.normalize();

        mCameraComponent->eyePosition += righOrientation * adjustedSpeed;
    
    }
    
    if (glfwGetKey(Game::window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        mCameraComponent->eyePosition +=  Vector3D::UP() * adjustedSpeed;
    }
    if (glfwGetKey(Game::window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        Vector3D down = Vector3D::UP() * -1.0f;


        mCameraComponent->eyePosition += down * adjustedSpeed;
    
    }
    if (glfwGetKey(Game::window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        adjustedSpeed = 0.4f;
    }
    else if (glfwGetKey(Game::window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        adjustedSpeed = 0.1f;
    }


}

void MainCamera::RotationCamera(float deltaTime)
{

    // Handles mouse inputs
	if (glfwGetMouseButton(Game::window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(Game::window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(Game::window, (Game::Width / 2), (Game::Height / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(Game::window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (Game::Height / 2)) / Game::Height;
		float rotY = sensitivity * (float)(mouseX - (Game::Width / 2)) / Game::Width;

	
		Vector3D newCross = Vector3D::Cross(mCameraComponent->orientation,Vector3D::UP()).normalize();
		
		Vector3D newOrientation = Vector3D::Rotation(mCameraComponent->orientation, newCross, RadToDegree::ToRadians(-rotX));

		
		
		if (abs(Vector3D::AngleInRad(newOrientation,Vector3D::UP()) - RadToDegree::ToRadians(90.0f)) <= RadToDegree::ToRadians(85.0f))
		{
			mCameraComponent->orientation = newOrientation;
		}
				
		
		mCameraComponent->orientation = Vector3D::Rotation(mCameraComponent->orientation,Vector3D::UP(),RadToDegree::ToRadians(-rotY));

        //std::cout << mCameraComponent->orientation << std::endl;

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(Game::window, (Game::Width / 2), (Game::Height / 2));
	}
	else if (glfwGetMouseButton(Game::window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(Game::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}


}

