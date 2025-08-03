//MyWindow.cpp
#include "Common.h"
#include <stdexcept>


MyWindow::MyWindow(int width, int height, const std::string& title) 
{
    if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //Disable window resizing.

    _window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!_window) 
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);

    //glfwSetScrollCallback(_window, &_renderer);
}

MyWindow::~MyWindow() 
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}

bool MyWindow::ShouldClose() const //Best practice: mark any accessor-getter func as const when it doesn’t need to change anything.
{
    return glfwWindowShouldClose(_window);
}

void MyWindow::PollEvents() const 
{
    glfwPollEvents();
}

void MyWindow::SwapBuffers() const 
{
    glfwSwapBuffers(_window);
}

GLFWwindow* MyWindow::GetGLFWwindow() const 
{
    return _window;
}