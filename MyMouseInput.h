
#pragma once
#include "MyInputComponent.h"
#include "Common.h"

class MyMouseInput : public MyInputComponent
{
    public:

        MyMouseInput(GLFWwindow* window);
        void Update(float deltaTime) override;

        double GetX() const { return _x; }
        double GetY() const { return _y; }
        bool IsLeftClicked() const { return _leftClicked; }
        bool IsMiddleClicked() const { return _middleClicked; }
        bool IsRightClicked() const { return _rightClicked; }
        bool AnyMouseButtonClicked();

    private:
        GLFWwindow* _window;
        double _x, _y;
        bool _leftClicked;
        bool _middleClicked;
        bool _rightClicked;
};
