#pragma once
//#include "Common.h"
#include "MyWindow.h"
#include "MyMesh.h"
#include "MyShader.h"
#include "MyCamera.h"
class MyBitmapFontRenderer;

class MyGlyphRenderer
{
    public:

        MyGlyphRenderer(MyWindow& window, float FOV, float FAR);
        ~MyGlyphRenderer();

        void Render(float deltaTime, float fps, float mouseX, float mouseY, int triCount, int quadCount);

        MyCamera& GetCamera() { return _camera; }

    private:

        MyCamera _camera;
        const float _renderViewWidth = 800.0f;
        const float _renderViewHeight = 600.0f;
        void Draw(float fps, float mouseX, float mouseY, int triCount, int quadCount);

        MyBitmapFontRenderer* _fontRenderer;
        unsigned int _textShader;

        std::string _fpsText;
        std::string _mouseClickPosText;
        std::string _trisRenderedCountText;
        std::string _quadRenderedCountText;
        std::string _mouseControlHelpText;

        static const char* _sTextVertShaderPathStr;
        static const char* _sTextFragShaderPathStr;
        static const char* _sFontShaderPathStr;


};
