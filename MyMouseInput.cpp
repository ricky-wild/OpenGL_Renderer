#include "MyMouseInput.h"


MyMouseInput::MyMouseInput(GLFWwindow* window) : _window(window), _x(0), _y(0), _leftClicked(false), _middleClicked(false), _rightClicked(false)
{

}

void MyMouseInput::Update(float deltaTime)
{
    double currentX, currentY;
    glfwGetCursorPos(_window, &currentX, &currentY);

    if (_firstUpdate) 
    {
        _lastX = currentX;
        _lastY = currentY;
        _firstUpdate = false;
    }

    //Save current first and don't overwrite _last just yet.
    _x = currentX;
    _y = currentY;

    _leftClicked = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    _middleClicked = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
    _rightClicked = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

}

void MyMouseInput::HandleInput(MyCamera* camera)
{
    double mouseX = GetX();
    double mouseY = GetY();

    if (AnyMouseButtonClicked()) 
    {

    }

    if (IsRightClicked()) 
    {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        camera->ProcessMouseMovement((float)GetDeltaX(), (float)-GetDeltaY());
        SetLastPositionToCurrent();
    }
    else
    {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (IsLeftClicked()) 
    {
        camera->ResetCameraPoisition();
    }


}

void MyMouseInput::SetLastPositionToCurrent()
{
    _lastX = _x;
    _lastY = _y;
}

bool MyMouseInput::AnyMouseButtonClicked()
{
    if (_leftClicked) return true;
    if (_middleClicked) return true;
    if (_rightClicked) return true;

    return false;
}