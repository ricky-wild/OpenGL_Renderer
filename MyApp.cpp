
#include "MyApp.h"
#include "MyWindow.h"
#include "MyMeshRenderer.h"
#include "MyQuadRenderer.h"
#include "MyGlyphRenderer.h"

const int TRI_COUNT = 500;

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

    _meshRenderer = new MyMeshRenderer(*_window, 45.0f, 200.0f, TRI_COUNT);
    //_quadRenderer = new MyQuadRenderer(*_window, 45.0f, 200.0f);
    _glyphRenderer = new MyGlyphRenderer(*_window, 45.0f, 200.0f);
    _quadRenderer = new MyQuadRenderer(*_window, 45.0f, 200.0f);
    s_cameraPtr = &_meshRenderer->GetCamera();

    glfwSetScrollCallback(_window->GetGLFWwindow(), ScrollCallback);

    
    _mouseInput = new MyMouseInput(_window->GetGLFWwindow());
    


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
    delete _meshRenderer;
    delete _quadRenderer;
    delete _glyphRenderer;
    delete _window;
}

void MyApp::Run()
{


    //double mouseX = 0.0;
    //double mouseY = 0.0;

    while (!_window->ShouldClose())
    {
        CalculateFPS();


        _mouseInput->Update(_deltaTime);
        _mouseInput->HandleInput(_meshRenderer);
        //_mouseInput->HandleInput(_meshRenderer, _quadRenderer, _glyphRenderer);

        _window->PollEvents();

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        _meshRenderer->Render(_deltaTime);
        _glyphRenderer->Render(_deltaTime, _currentFPS, _mouseInput->GetX(), _mouseInput->GetY(), TRI_COUNT);
        _quadRenderer->Render(_deltaTime);


        //glBindVertexArray(0);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);

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


