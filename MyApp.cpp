
#include "MyApp.h"
#include "MyWindow.h"
#include "MyMeshRenderer.h"
#include "MyQuadRenderer.h"
#include "MyGlyphRenderer.h"

const int TRI_MESH_COUNT = 500;
const int QUAD_MESH_COUNT = 100;//50;

//Static pointer & method required for openGL glfwSetScrollCallback() arg.
static MyCamera* s_cameraPtr = nullptr;
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (s_cameraPtr) s_cameraPtr->ProcessMouseScroll(static_cast<float>(yoffset));
}


MyApp::MyApp()
{

    _window = new MyWindow(_winWidth, _winHeight, "wildlogicgames - opengl app");

    float FOV = 90.0f; //45.0f;
    float nearPlane = 0.1f;
    float farPlane = 200.0f;
    _camera = new MyCamera(FOV, _winWidth / _winHeight, nearPlane, farPlane);

    glfwSwapInterval(0); // Disable V-Sync for uncapped FPS. 1 enable the cap.

    _meshRenderer = new MyMeshRenderer(*_window, 45.0f, 200.0f, TRI_MESH_COUNT);
    _glyphRenderer = new MyGlyphRenderer(*_window, 45.0f, 200.0f);

    float Scale = 1.0f;
    float PosX = -1.0f;
    float PosY = 0.0f;
    float PosZ = 0.0f;
    _quadRenderer = new MyQuadRenderer(*_window, 45.0f, 200.0f);

    for (int i = 0; i < QUAD_MESH_COUNT; i++)
    {
        _quadRenderer->AddQuad({ PosX, PosY, PosZ }, { 0.0f, 0.0f, 0.0f }, { Scale, Scale, Scale });
        
        if (i < QUAD_MESH_COUNT / 2)
        {
            PosX += 0.5f;
            PosZ -= 2.0f;
            PosY += 0.5f;
        }
        else
        {
            PosX += 0.5f;
            PosZ += 2.0f;
            PosY -= 0.5f;
        }
    }





    s_cameraPtr = _camera;
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

    while (!_window->ShouldClose())
    {
        CalculateFPS();


        _mouseInput->Update(_deltaTime);
        _mouseInput->HandleInput(_camera);
        _window->PollEvents();

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        _meshRenderer->Render(_deltaTime, _camera->GetViewMatrix(), _camera->GetProjectionMatrix());
        _quadRenderer->Render(_deltaTime, _camera->GetViewMatrix(), _camera->GetProjectionMatrix());
        _glyphRenderer->Render(_deltaTime, _currentFPS, _mouseInput->GetX(), _mouseInput->GetY(), TRI_MESH_COUNT, QUAD_MESH_COUNT);
        

        _camera->Update(_deltaTime);


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


