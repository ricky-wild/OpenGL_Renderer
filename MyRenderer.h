
//class IRenderable
//{
//    public:
//        virtual void Update(float dt) = 0;
//        virtual void Draw() const = 0;
//        virtual ~IRenderable() = default;
//};
#pragma once
#include "MyWindow.h"
#include "MyMesh.h"
#include "MyShader.h"
#include "MyCamera.h"

class MyRenderer 
{
    public:
        MyRenderer(MyWindow& window);
        ~MyRenderer();

        void Render(float dt);
        void Draw();
        void Update(float deltaTime);

        void AddMesh(MyMesh* mesh);

    private:
        void InitGL();
        void InitTriangle();

        std::vector<float> _triangleVertices;
        std::vector<MyMesh*> _renderables;

        float _vertPointVal;
        MyShader* _shader;
        MyCamera _camera;
};
