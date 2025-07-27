
//MyRenderer.cpp
#include "Common.h"
#include <cmath>



MyRenderer::MyRenderer(MyWindow& window) 
{
    glfwMakeContextCurrent(window.GetGLFWwindow());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    InitGL();
    InitTraingleVertices();
    InitTriangleMeshes();

    //_triangleMesh = new MyMesh(_triangleVertices);
}

MyRenderer::~MyRenderer() 
{
    //delete _triangleMesh;


    _triangleVertices.clear();

    for (MyMesh* mesh : _triangleMeshList)
        delete mesh;
    _triangleMeshList.clear();
}

void MyRenderer::InitGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void MyRenderer::InitTraingleVertices()
{
    _vertPointVal = 0.15f;

    _triangleVertices = 
    {
         0.0f,  _vertPointVal, 0.0f,            //top
        -_vertPointVal, -_vertPointVal, 0.0f,  //bottom left
         _vertPointVal, -_vertPointVal, 0.0f   //bottom right
    };
}

void MyRenderer::InitTriangleMeshes()
{
    const int traingleCount = 3;
    const float xSpacing = 0.4f;
    float vert = _vertPointVal;
    float spacing = xSpacing;

    for (int i = 0; i < traingleCount; ++i)
    {
        float xOffset = i * spacing;

        std::vector<float> triangle = 
        {
             0.0f + xOffset,  vert, 0.0f,
            -vert + xOffset, -vert, 0.0f,
             vert + xOffset, -vert, 0.0f
        };

        _triangleMeshList.push_back(new MyMesh(triangle));
        vert = vert / 1.25f;

    }
}

void MyRenderer::Render(float deltaTime) 
{
    glClear(GL_COLOR_BUFFER_BIT);

    //for (MyMesh* mesh : _triangleMeshList)
    //    mesh->Draw();


    
    for (MyMesh* mesh : _triangleMeshList) 
    {
        mesh->Update(deltaTime);
        mesh->Draw();
    }

}
