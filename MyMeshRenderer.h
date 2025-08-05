#pragma once
//#include "Common.h"
#include "MyWindow.h"
#include "MyMesh.h"
#include "MyShader.h"
#include "MyCamera.h"

class MyMeshRenderer
{
    public:

        MyMeshRenderer(MyWindow& window, float FOV, float FAR, int triangleCount);
        ~MyMeshRenderer();

        void Render(float deltaTime);


        MyCamera& GetCamera() { return _camera; }

    private:



        void InitTriangles(int triCount);
        void Draw();
        void Update(float deltaTime);
        void AddMesh(MyMesh* mesh);


        std::vector<float> _triangleVertices; //vector is dynamic array provided c++ STL. v cool.
        std::vector<MyMesh*> _renderables;

        const float _renderViewWidth = 800.0f;
        const float _renderViewHeight = 600.0f;

        static const char* _sBasicVertShaderPathStr;
        static const char* _sBasicFragShaderPathStr;


        MyShader* _shader;
        MyCamera _camera;

};
