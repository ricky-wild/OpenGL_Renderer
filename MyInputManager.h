
#pragma once
#include "Common.h"
#include "MyInputComponent.h"

class MyInputManager 

{
    public:

        void AddComponent(MyInputComponent* input);
        void Update(float deltaTime);

    private:
        std::vector<MyInputComponent*> _inputs;

};
