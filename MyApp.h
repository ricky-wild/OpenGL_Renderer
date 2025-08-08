

#pragma once

//Forward declarations.
class MyWindow;   
class MyCamera;
class MyMeshRenderer;
class MyQuadRenderer;
class MyGlyphRenderer;
class MyMouseInput;
class MyInputManager;

class MyApp
{
    public:

        MyApp();
        ~MyApp();

        void Run();

    private:

        float _currentTime;
        float _deltaTime;
        float _lastTime;
        float _timeAccumulator;
        float _currentFPS;
        int _frameCount;
        const float _winWidth = 800.0f; 
        const float _winHeight = 600.0f;

        void CalculateFPS();

        //forward declarations
        MyWindow* _window; 
        MyCamera* _camera;
        MyQuadRenderer* _quadRenderer;
        MyMeshRenderer* _meshRenderer;
        MyGlyphRenderer* _glyphRenderer;

        MyInputManager* _inputManager;
        MyMouseInput* _mouseInput;
};
