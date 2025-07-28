

#pragma once

class MyWindow;   // forward declaration
class MyRenderer; // forward declaration

class MyApp
{
    public:
        MyApp();
        ~MyApp();
        void Run();

    private:
        MyWindow* _window;       // use pointers to allow forward declarations
        MyRenderer* _renderer;
};
