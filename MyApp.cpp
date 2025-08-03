
#include "MyApp.h"
#include "MyWindow.h"
#include "MyRenderer.h"


//Static pointer & method required for openGL glfwSetScrollCallback() arg.
static MyCamera* s_cameraPtr = nullptr;
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (s_cameraPtr) s_cameraPtr->ProcessMouseScroll(static_cast<float>(yoffset));
}


MyApp::MyApp()
{

    _window = new MyWindow(800, 600, "wildlogicgames - opengl app");

    glfwSwapInterval(0); // Disable V-Sync for uncapped FPS. 1 enable the cap.

    _renderer = new MyRenderer(*_window);


    //glfwSetScrollCallback() raw C-style function, which can’t access non-static members or lambdas with captures.
    s_cameraPtr = &_renderer->GetCamera();
    glfwSetScrollCallback(_window->GetGLFWwindow(), ScrollCallback);

    //_inputManager = new MyInputManager();
    _mouseInput = new MyMouseInput(_window->GetGLFWwindow());
    //_inputManager->AddComponent(_mouseInput);


    _lastTime = 0.0f;
    _timeAccumulator = 0.0f;
    _frameCount = 0;
    _currentFPS = 0.0f;
    _currentTime = 0.0f;
    _deltaTime = 0.0f;
}

MyApp::~MyApp()
{
    delete _mouseInput;
    //delete _inputManager;
    delete _renderer;
    delete _window;
}

void MyApp::Run()
{


    //double mouseX = 0.0;
    //double mouseY = 0.0;

    while (!_window->ShouldClose())
    {
        CalculateFPS();

        //_inputManager->Update(_deltaTime);
        //_inputManager->HandleInput(_renderer);
        _mouseInput->Update(_deltaTime);
        _mouseInput->HandleInput(_renderer);

        _window->PollEvents();
        _renderer->Render(_deltaTime, _currentFPS, _mouseInput->GetX(), _mouseInput->GetY());
        _window->SwapBuffers();
    }
}

void MyApp::CalculateFPS()
{
    _currentTime = glfwGetTime();
    _deltaTime = _currentTime - _lastTime;
    _lastTime = _currentTime;

    _timeAccumulator += _deltaTime;
    _frameCount++;


    if (_timeAccumulator >= 1.0f)
    {
        _currentFPS = _frameCount / _timeAccumulator;
        _frameCount = 0;
        _timeAccumulator = 0.0f;
    }
}


