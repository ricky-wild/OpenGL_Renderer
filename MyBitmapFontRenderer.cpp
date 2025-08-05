#include "MyBitmapFontRenderer.h"




MyBitmapFontRenderer::MyBitmapFontRenderer(MyShader* shader, unsigned int screenWidth, unsigned int screenHeight)
    : _shader(shader), 
      _screenWidth(screenWidth), 
      _screenHeight(screenHeight)
{
    Init();

    //glGenTextures(1, &_fontTexture);
    //glBindTexture(GL_TEXTURE_2D, _fontTexture);

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(screenWidth),
        0.0f, static_cast<float>(screenHeight));

    _shader->Use();
    _shader->SetMat4("projection", projection);


}

void MyBitmapFontRenderer::LoadFontTexture(const std::string& path)
{
    //Init();



    //glGenTextures(1, &_fontTexture);
    //glBindTexture(GL_TEXTURE_2D, _fontTexture);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 4);
    if (!data)
    {
        std::cerr << "Failed to load font texture: " << path << std::endl;
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
        0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(data);


}

void MyBitmapFontRenderer::Init()
{
    if (_VAO != 0) return; //Guard clause

    //0 corrisponds the shader layout location ie the atrribute point assigned in the .vert file (layout location = 0)
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ...);
    //glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   //<-- important!! Unbind buffer
    glBindVertexArray(0);              //and then unbind VAO



}

void MyBitmapFontRenderer::RenderText(const std::string& text, float x, float y, float scale, const glm::vec3& color)
{
    if (!_shader) return; // early exit or assert



    _shader->Use();
    //glUniform3f(glGetUniformLocation(_shader->GetID(), "textColor"), color.r, color.g, color.b);
    //glUniform3f(glGetUniformLocation(_shader->GetID(), "textColor"), color.r, color.g, color.b); 
    _shader->SetVec3("textColor", color);



    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(_VAO);
    glBindTexture(GL_TEXTURE_2D, _fontTexture);

    float charSize = _charWidth * scale;

    for (char c : text)
    {
        int ascii = static_cast<unsigned char>(c);
        int row = ascii / _glyphsPerRow;
        int col = ascii % _glyphsPerRow;

        float tx = col / (float)_glyphsPerRow;
        float ty = row / (float)_glyphsPerRow;
        float ts = 1.0f / _glyphsPerRow;

        float xpos = x;
        float ypos = y;

        float vertices[6][4] =
        {
            {
                xpos,
                ypos + charSize,
                tx,
                ty,
            },

            {
                xpos,
                ypos,
                tx,
                ty + ts,
            },

            {
                xpos + charSize,
                ypos,
                tx + ts,
                ty + ts,
            },

            {
                xpos,
                ypos + charSize,
                tx,
                ty,
            },

            {
                xpos + charSize,
                ypos,
                tx + ts,
                ty + ts,
            },

            {
                xpos + charSize,
                ypos + charSize,
                tx + ts,
                ty,
            },

        };

        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        float spacingFactor = 0.75f;
        float glyphAdvance = _charWidth * scale * spacingFactor;
        x += glyphAdvance;
        //float spacingFactor = 0.75f; // below 0.75f starts to clip the glyph.
        //x += charSize * spacingFactor;
        // 
        //x += charSize;
    }


    //glBindVertexArray(0);
    //glBindTexture(GL_TEXTURE_2D, 0);
}
