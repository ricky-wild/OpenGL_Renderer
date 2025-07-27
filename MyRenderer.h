

//MyRenderer.h
#pragma once
#include "Common.h"
#include "MyMesh.h"

class MyRenderer 
{
    public:
        MyRenderer(MyWindow& window);
        ~MyRenderer();
        void Render(float dt);

    private:
        void InitGL();

        void InitTraingleVertices();
        void InitTriangleMeshes();

        std::vector<float> _triangleVertices;
        std::vector<MyMesh*> _triangleMeshList;

        float _vertPointVal;
};
