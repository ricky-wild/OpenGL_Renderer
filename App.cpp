

// App.cpp
#include "Common.h"

App::App() : _window(800, 600, "wildlogicgames - opengl"), _renderer(_window) {}
App::~App() {}

void App::Run() 
{
    float lastTime = glfwGetTime();

    while (!_window.ShouldClose()) 
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        _window.PollEvents();
        _renderer.Render(deltaTime);
        _window.SwapBuffers();
    }
}




