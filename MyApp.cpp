
#include "MyApp.h"
#include "MyWindow.h"
#include "MyRenderer.h"



MyApp::MyApp()
{

    _window = new MyWindow(800, 600, "wildlogicgames - opengl app");
    glfwSwapInterval(0); // Disable V-Sync for uncapped FPS. 1 enable the cap.
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
    float timeAccumulator = 0.0f;
    int frameCount = 0;
    float currentFPS = 0.0f;

    while (!_window->ShouldClose())
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        timeAccumulator += deltaTime;
        frameCount++;


        if (timeAccumulator >= 1.0f)
        {
            currentFPS = frameCount / timeAccumulator; 
            frameCount = 0;
            timeAccumulator = 0.0f;
        }

        _window->PollEvents();
        _renderer->Render(deltaTime, currentFPS); 
        _window->SwapBuffers();
    }
}

//void MyApp::Run()
//{
//    float lastTime = glfwGetTime();
//
//    while (!_window->ShouldClose())
//    {
//        float currentTime = glfwGetTime();
//        float deltaTime = currentTime - lastTime;
//        lastTime = currentTime;
//
//        _window->PollEvents();
//        _renderer->Render(deltaTime);
//        _window->SwapBuffers();
//    }
//}


