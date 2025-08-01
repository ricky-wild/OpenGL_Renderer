#include "MyInputManager.h"

void MyInputManager::AddComponent(MyInputComponent* input)
{
    _inputs.push_back(input);
}

void MyInputManager::Update(float deltaTime)
{

    for (auto* input : _inputs)
        input->Update(deltaTime);

}