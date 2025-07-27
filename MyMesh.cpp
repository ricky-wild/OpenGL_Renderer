// MyMesh.cpp
#include "Common.h"


MyMesh::MyMesh(const std::vector<float>& vertices)
    : _originalVertices(vertices), _transformedVertices(vertices)
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _transformedVertices.size() * sizeof(float), _transformedVertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

MyMesh::~MyMesh()
{
    glDeleteBuffers(1, &_VBO);
    glDeleteVertexArrays(1, &_VAO);
}

void MyMesh::Update(float deltaTime)
{
    _rotationAngle += 90.0f * deltaTime; // degrees per second
    if (_rotationAngle > 360.0f) _rotationAngle -= 360.0f;
    UpdateRotation();
}

void MyMesh::UpdateRotation()
{
    float radians = glm::radians(_rotationAngle);
    float cosA = cosf(radians);
    float sinA = sinf(radians);

    _transformedVertices.clear();
    for (size_t i = 0; i < _originalVertices.size(); i += 3)
    {
        float x = _originalVertices[i];
        float y = _originalVertices[i + 1];
        float z = _originalVertices[i + 2];

        float rotatedX = x * cosA + z * sinA;
        float rotatedY = y;  // Y remains unchanged
        float rotatedZ = -x * sinA + z * cosA;

        _transformedVertices.push_back(rotatedX);
        _transformedVertices.push_back(rotatedY);
        _transformedVertices.push_back(rotatedZ);
    }

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, _transformedVertices.size() * sizeof(float), _transformedVertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MyMesh::Draw() const
{
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
