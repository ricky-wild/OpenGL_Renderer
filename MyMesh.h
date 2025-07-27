//MyMesh.h
#pragma once
#include "Common.h"

class MyMesh 
{
    public:
        MyMesh(const std::vector<float>& vertices);
        ~MyMesh();

        void Draw() const;
        void Update(float deltaTime);

    private:
        GLuint _VAO, _VBO;

        float _rotationAngle = 0.0f; // in degrees

        std::vector<float> _originalVertices;
        std::vector<float> _transformedVertices;

        void UpdateRotation();
};