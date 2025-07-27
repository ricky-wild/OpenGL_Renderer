//MyWindow.cpp
#include "Common.h"
#include <stdexcept>

MyWindow::MyWindow(int width, int height, const std::string& title) 
{
    if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

MyWindow::~MyWindow() 
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool MyWindow::ShouldClose() const 
{
    return glfwWindowShouldClose(window);
}

void MyWindow::PollEvents() const 
{
    glfwPollEvents();
}

void MyWindow::SwapBuffers() const 
{
    glfwSwapBuffers(window);
}

GLFWwindow* MyWindow::GetGLFWwindow() const 
{
    return window;
}