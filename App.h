// App.h
#pragma once
#include "MyWindow.h"
#include "MyRenderer.h"

class App
{
    public:
        App();
        ~App();
        void Run();

    private:
        MyWindow _window;
        MyRenderer _renderer;
};