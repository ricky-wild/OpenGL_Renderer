

#pragma once

//Forward declarations.
class MyWindow;   
class MyRenderer; 
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

        MyWindow* _window;       //pointers allow for forward declarations
        MyRenderer* _renderer;


        MyInputManager* _inputManager;
        MyMouseInput* _mouseInput;
};
