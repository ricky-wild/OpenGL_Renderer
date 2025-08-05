
#include "Common.h"


MyMesh::MyMesh(const std::vector<float>& vertices, RenderMode renderMode)
    : _vertices(vertices),
      _renderMode(renderMode),
      _vertexCount(vertices.size() / 3),
      _modelMatrix(glm::mat4(1.0f)) // assuming 3 floats per vertex
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

MyMesh::MyMesh(const std::vector<float>& vertices, const std::vector<float>& texCoords, RenderMode renderMode)
    : _vertices(vertices), 
      _texCoords(texCoords), 
      _renderMode(renderMode), 
      _vertexCount(vertices.size() / 3), 
      _modelMatrix(glm::mat4(1.0f))
{




    //Interleave position and texture coordinates into one buffer
    std::vector<float> interleaved;
    for (size_t i = 0; i < vertices.size() / 3; ++i)
    {
        interleaved.push_back(vertices[i * 3 + 0]); // x
        interleaved.push_back(vertices[i * 3 + 1]); // y
        interleaved.push_back(vertices[i * 3 + 2]); // z

        if (!texCoords.empty()) 
        {
            interleaved.push_back(texCoords[i * 2 + 0]); // u
            interleaved.push_back(texCoords[i * 2 + 1]); // v
        }
        else 
        {
            interleaved.push_back(0.0f); // default UV
            interleaved.push_back(0.0f);
        }
    }

    //Put interleaved data on GPU
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, interleaved.size() * sizeof(float), interleaved.data(), GL_STATIC_DRAW);


    //Attribute 0, Position x, y and z
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Attribute 1, TexCoords u, v
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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

    if (_renderMode == RenderMode::Textured)
    {
        if (_textureID != 0)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _textureID);
            shader.Use();
            shader.SetInt("my_U_texture", 0); //sampler2D uniform read from unit 0
        }
        int loc = glGetUniformLocation(shader.GetID(), "my_U_texture");
        if (loc == -1) std::cerr << "Uniform 'my_U_texture' not active or missing\n";
    }

    //shader.SetMat4("u_Model", _modelMatrix);

    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, _vertexCount);//glDrawArrays(GL_TRIANGLES, 0, 3);
    //glBindVertexArray(0);

    //glBindVertexArray(_VAO);




    //glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
    //glBindVertexArray(0);



    //glDrawArrays(GL_TRIANGLES, 0, _vertexCount);//glDrawArrays(GL_TRIANGLES, 0, 3);
    //glBindVertexArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //glUseProgram(0);
    //glBindTexture(GL_TEXTURE_2D, 0);
}

void MyMesh::SetTexture(unsigned int textureID)
{
    _textureID = textureID;
}

