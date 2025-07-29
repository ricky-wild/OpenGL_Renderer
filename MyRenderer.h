

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

        void Render(float dt, float fps);
        void Draw(float fps);
        void Update(float deltaTime);

        void AddMesh(MyMesh* mesh);

    private:

        void InitGL();
        void InitTriangle();

        std::vector<float> _triangleVertices;
        std::vector<MyMesh*> _renderables;

        const float _renderViewWidth = 800.0f;
        const float _renderViewHeight = 600.0f;

        MyShader* _shader;
        MyCamera _camera;

        MyBitmapFontRenderer* _fontRenderer;
        unsigned int _textShader;
};
