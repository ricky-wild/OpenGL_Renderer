
#pragma once

class MyInputComponent 
{
    public:

        virtual ~MyInputComponent() = default;
        virtual void Update(float deltaTime) = 0;

};
