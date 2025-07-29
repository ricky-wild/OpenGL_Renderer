#pragma once

#include <string>
#include "Common.h"
#include "stb_image.h"
//#include "MyShader.h"
class MyShader;

class MyBitmapFontRenderer
{

    public:

        MyBitmapFontRenderer(MyShader* shader, unsigned int screenWidth, unsigned int screenHeight);
        void LoadFontTexture(const std::string& path);
        void RenderText(const std::string& text, float x, float y, float scale, const glm::vec3& color);

    private:

        unsigned int _VAO, _VBO;
        unsigned int _fontTexture;
        MyShader* _shader;
        unsigned int _screenWidth;
        unsigned int _screenHeight;

        const int _glyphsPerRow = 16;
        const int _charWidth = 16;
        const int _charHeight = 16;

        void Init();
};
