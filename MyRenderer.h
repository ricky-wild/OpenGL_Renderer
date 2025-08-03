

#pragma once
//#include "Common.h"
#include "MyWindow.h"
#include "MyMesh.h"
//#include "MyBitmapFontRenderer.h"
class MyBitmapFontRenderer;
#include "MyShader.h"
#include "MyCamera.h"


class MyRenderer 
{
    public:

        MyRenderer(MyWindow& window);
        ~MyRenderer();

        void Render(float dt, float fps, float mouseX, float mouseY);
        void Draw(float fps, float mouseX, float mouseY);
        void Update(float deltaTime);

        void AddMesh(MyMesh* mesh);

        MyCamera& GetCamera() { return _camera; }

    private:

        void InitGL();
        void InitTriangles(int triCount);

        std::vector<float> _triangleVertices; //vector is dynamic array provided c++ STL. v cool.
        std::vector<MyMesh*> _renderables;

        const float _renderViewWidth = 800.0f;
        const float _renderViewHeight = 600.0f;

        MyShader* _shader;
        MyCamera _camera;

        //unsigned int _batchVAO = 0;
        //unsigned int _batchVBO = 0;
        //int _totalVertices = 0;

        MyBitmapFontRenderer* _fontRenderer;
        unsigned int _textShader;

        std::string _fpsText;
        std::string _mouseClickPosText;
        std::string _trisRenderedCountText;
        static const char* _sBasicVertShaderPathStr;
        static const char* _sBasicFragShaderPathStr;
        static const char* _sTextVertShaderPathStr;
        static const char* _sTextFragShaderPathStr;
        static const char* _sFontShaderPathStr;
};
