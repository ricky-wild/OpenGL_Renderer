//MyWindow.h


#pragma once
#include "Common.h"

class MyWindow 
{
    public:

        MyWindow(int width, int height, const std::string& title);
        ~MyWindow();

        bool ShouldClose() const;
        void PollEvents() const;
        void SwapBuffers() const;
        GLFWwindow* GetGLFWwindow() const;

    private:

        GLFWwindow* _window;

};