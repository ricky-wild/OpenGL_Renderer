#pragma once
//#include "Common.h"
#include "MyWindow.h"
#include "MyMesh.h"
#include "MyShader.h"
#include "MyCamera.h"

class MyQuadRenderer
{
    public:

        MyQuadRenderer(MyWindow& window, float FOV, float FAR);
        ~MyQuadRenderer();

        void Render(float dt);


        MyCamera& GetCamera() { return _camera; }

    private:

    
        unsigned int LoadTexture(const std::string& path);

        void InitQuad();
        void Draw();
        void Update(float deltaTime);
        void AddMesh(MyMesh* mesh);
    

        std::vector<float> _triangleVertices; //vector is dynamic array provided c++ STL. v cool.
        std::vector<MyMesh*> _renderables;

        const float _renderViewWidth = 800.0f;
        const float _renderViewHeight = 600.0f;

        static const char* _sTextureVertShaderPathStr;
        static const char* _sTextureFragShaderPathStr;
        static const char* _sTextureFilePathStr;

        MyShader* _shader;
        MyCamera _camera;

};
