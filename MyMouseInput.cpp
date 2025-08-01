#include "MyMouseInput.h"


MyMouseInput::MyMouseInput(GLFWwindow* window) : _window(window), _x(0), _y(0), _leftClicked(false), _middleClicked(false), _rightClicked(false)
{

}

void MyMouseInput::Update(float deltaTime)
{
    glfwGetCursorPos(_window, &_x, &_y);
    _leftClicked = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    _middleClicked = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
    _rightClicked = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

bool MyMouseInput::AnyMouseButtonClicked()
{
    if (_leftClicked) return true;
    if (_middleClicked) return true;
    if (_rightClicked) return true;

    return false;
}