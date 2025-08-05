//MyMesh.h


#pragma once

class MyShader;   // forward declaration
#include "RenderMode.h"

class MyMesh 
{
    public:

        MyMesh(const std::vector<float>& vertices, RenderMode renderMode = RenderMode::BasicColor);
        MyMesh(const std::vector<float>& vertices, const std::vector<float>& texCoords, RenderMode renderMode);


        ~MyMesh();

        void Draw(MyShader& shader) const;
        void Update(float deltaTime);

        RenderMode GetRenderMode() const { return _renderMode; }
        void SetTexture(unsigned int textureID);

        //Transform properties
        glm::vec3 _tPosition = glm::vec3(0.0f);
        glm::vec3 _tRotation = glm::vec3(0.0f); //degrees
        glm::vec3 _tScale = glm::vec3(1.0f);

    private:

        GLuint _VAO, _VBO;//, _TBO;

        RenderMode _renderMode;

        int _vertexCount = 0;
        std::vector<float> _vertices;

        unsigned int _textureID = 0;
        std::vector<float> _texCoords;

        mutable glm::mat4 _modelMatrix;

        void UpdateModelMatrix();

};