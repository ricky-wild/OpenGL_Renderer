

#pragma once

//Forward declarations.
class MyWindow;   
//class MyRenderer; 
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

        void CalculateFPS();

        //forward declarations
        MyWindow* _window;      
        MyQuadRenderer* _quadRenderer;
        MyMeshRenderer* _meshRenderer;
        MyGlyphRenderer* _glyphRenderer;

        MyInputManager* _inputManager;
        MyMouseInput* _mouseInput;
};
