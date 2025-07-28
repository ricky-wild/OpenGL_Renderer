
#include "MyApp.h"
#include "MyWindow.h"
#include "MyRenderer.h"



MyApp::MyApp()
{
    _window = new MyWindow(800, 600, "wildlogicgames - opengl app");
    _renderer = new MyRenderer(*_window);
}

MyApp::~MyApp()
{
    delete _renderer;
    delete _window;
}


void MyApp::Run()
{
    float lastTime = glfwGetTime();

    while (!_window->ShouldClose())
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        _window->PollEvents();
        _renderer->Render(deltaTime);
        _window->SwapBuffers();
    }
}


