
#include "Common.h"


MyMesh::MyMesh(const std::vector<float>& vertices)
    : _vertices(vertices), _vertexCount(vertices.size() / 3), _modelMatrix(glm::mat4(1.0f)) // assuming 3 floats per vertex
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // Unbind VAO


}

MyMesh::~MyMesh()
{
    glDeleteBuffers(1, &_VBO);
    glDeleteVertexArrays(1, &_VAO);
}

void MyMesh::Update(float deltaTime)
{
    _tRotation.y += deltaTime * 45.0f;


    UpdateModelMatrix();
}

void MyMesh::UpdateModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, _tPosition);
    model = glm::rotate(model, glm::radians(_tRotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(_tRotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(_tRotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, _tScale);
    _modelMatrix = model;
}

void MyMesh::Draw(MyShader& shader) const
{

    shader.SetMat4("u_Model", _modelMatrix);

    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, _vertexCount);//glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}