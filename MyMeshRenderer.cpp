#include "MyMeshRenderer.h"

#ifdef _DEBUG
const char* MyMeshRenderer::_sBasicVertShaderPathStr = "x64/Debug/shaders/basic.vert";
const char* MyMeshRenderer::_sBasicFragShaderPathStr = "x64/Debug/shaders/basic.frag";
#else
const char* MyMeshRenderer::_sBasicVertShaderPathStr = "shaders/basic.vert";
const char* MyMeshRenderer::_sBasicFragShaderPathStr = "shaders/basic.frag";
#endif



MyMeshRenderer::MyMeshRenderer(MyWindow& window, float FOV, float FAR, int triangleCount) : _camera(FOV, _renderViewWidth / _renderViewHeight, 0.1f, FAR) // fov, aspect, near, far
{
    glfwMakeContextCurrent(window.GetGLFWwindow());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    //glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    //glEnable(GL_DEPTH_TEST);

    _shader = new MyShader(_sBasicVertShaderPathStr, _sBasicFragShaderPathStr);
    InitTriangles(triangleCount);

}

MyMeshRenderer::~MyMeshRenderer()
{

    for (MyMesh* mesh : _renderables)
        delete mesh; //delete pointers.
    _renderables.clear();


}

void MyMeshRenderer::InitTriangles(int triCount)
{
    float vertPos = 0.075f;

    //Simple triangle, 3 verts with x, y and z.
    _triangleVertices =
    {
         0.0f,  vertPos, 0.0f,      // top
        -vertPos, -vertPos, 0.0f,   // bottom-left
         vertPos, -vertPos, 0.0f    // bottom-right
    };

    int triangleMeshCount = triCount;
    float x = 0.1f;
    float y = 0.03f;
    float z = 0.05f;


    for (int i = 0; i < triangleMeshCount; i++)
    {
        MyMesh* triangleMesh = new MyMesh(_triangleVertices, RenderMode::BasicColor);
        triangleMesh->_tPosition = glm::vec3(x, y, z);
        AddMesh(triangleMesh);
        x += 0.1f;


        if (i <= triangleMeshCount / 2)
        {
            y += 0.05f;
            z -= 0.05f;
        }
        else
        {
            y -= 0.1f;
            z += 0.05f;
        }



    }


}

void MyMeshRenderer::AddMesh(MyMesh* mesh)
{
    _renderables.push_back(mesh);
}

void MyMeshRenderer::Update(float deltaTime)
{

    for (MyMesh* mesh : _renderables)
        mesh->Update(deltaTime);

    _camera.Update(deltaTime);
}

void MyMeshRenderer::Draw()
{

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (MyMesh* mesh : _renderables)
    {

        _shader->Use();
        _shader->SetMat4("u_View", _camera.GetViewMatrix());
        _shader->SetMat4("u_Projection", _camera.GetProjectionMatrix());

        mesh->Draw(*_shader);
    }



    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MyMeshRenderer::Render(float deltaTime)
{
    Update(deltaTime);
    Draw();
}