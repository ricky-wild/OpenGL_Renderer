

#pragma once
//#include "Common.h"
#include "MyWindow.h"
#include "MyMesh.h"
#include "MyShader.h"
//#include "MyCamera.h"

class MyQuadRenderer
{
    public:

        MyQuadRenderer(MyWindow& window, float FOV, float FAR);
        ~MyQuadRenderer();

        void Render(float dt, const glm::mat4& viewMatrix, const glm::mat4& projMatrix);
        void AddQuad(const glm::vec3& pos,
                    const glm::vec3& rot = glm::vec3(0.0f),
                    const glm::vec3& scale = glm::vec3(1.0f));

        //MyCamera& GetCamera() { return _camera; }

    private:

    
        unsigned int LoadTexture(const std::string& path);

        //void InitQuad();
        void Draw(const glm::mat4& viewMatrix, const glm::mat4& projMatrix);
        void Update(float deltaTime);
        void AddMesh(MyMesh* mesh);
    

        std::vector<float> _triangleVertices; //vector is dynamic array provided c++ STL. v cool.
        std::vector<MyMesh*> _renderables;

        const float _renderViewWidth = 800.0f;
        const float _renderViewHeight = 600.0f;

        static const char* _sTextureVertShaderPathStr;
        static const char* _sTextureFragShaderPathStr;
        static const char* _sTextureFilePathStr;

        MyShader* _shader;
        //MyCamera _camera;

};
