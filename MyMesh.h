//MyMesh.h


#pragma once

class MyShader;   // forward declaration


class MyMesh 
{
    public:
        MyMesh(const std::vector<float>& vertices);
        ~MyMesh();

        void Draw(MyShader& shader) const;
        void Update(float deltaTime);

        //Transform properties
        glm::vec3 _tPosition = glm::vec3(0.0f);
        glm::vec3 _tRotation = glm::vec3(0.0f); //degrees
        glm::vec3 _tScale = glm::vec3(1.0f);

    private:
        GLuint _VAO, _VBO;


        int _vertexCount = 0;
        std::vector<float> _vertices;

        mutable glm::mat4 _modelMatrix;

        void UpdateModelMatrix();

};