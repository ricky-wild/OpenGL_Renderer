
#include "MyRenderer.h"



#ifdef _DEBUG
const char* MyRenderer::_sBasicVertShaderPathStr = "x64/Debug/shaders/basic.vert";
const char* MyRenderer::_sBasicFragShaderPathStr = "x64/Debug/shaders/basic.frag";
const char* MyRenderer::_sTextVertShaderPathStr = "x64/Debug/shaders/TextShader.vert";
const char* MyRenderer::_sTextFragShaderPathStr = "x64/Debug/shaders/TextShader.frag";
const char* MyRenderer::_sFontShaderPathStr = "x64/Debug/textures/font_atlas_01.png";
#else
const char* MyRenderer::_sBasicVertShaderPathStr = "shaders/basic.vert";
const char* MyRenderer::_sBasicFragShaderPathStr = "shaders/basic.frag";
const char* MyRenderer::_sTextVertShaderPathStr = "shaders/TextShader.vert";
const char* MyRenderer::_sTextFragShaderPathStr = "shaders/TextShader.frag";
const char* MyRenderer::_sFontShaderPathStr = "textures/font_atlas_01.png";
#endif









MyRenderer::MyRenderer(MyWindow& window) : _camera(45.0f, _renderViewWidth / _renderViewHeight, 0.1f, 100.0f) // fov, aspect, near, far
{
    glfwMakeContextCurrent(window.GetGLFWwindow());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    InitGL();

    _shader = new MyShader(_sBasicVertShaderPathStr, _sBasicFragShaderPathStr);
    InitTriangles(10);


    unsigned int w = 512;
    unsigned int h = 512;

    MyShader* textShader = new MyShader(_sTextVertShaderPathStr, _sTextFragShaderPathStr);
    std::cerr << "Text shader successfully loaded man!\n";

    _fontRenderer = new MyBitmapFontRenderer(textShader, w, h);
    std::cerr << "Font renderer successfully initialized bro!\n";

    _fontRenderer->LoadFontTexture(_sFontShaderPathStr);
    std::cerr << "Font texture successfully loaded dude!\n";

    _fontRenderer->RenderText("Hello", 15, 30, 0.5f, glm::vec3(1, 1, 0));
    std::cerr << "RenderText successfully called!\n";

    _camera.SetPosition(glm::vec3(0.0f, 0.1f, 2.0f));
    _camera.SetYawPitch(-90.0f, 0.0f);
}

MyRenderer::~MyRenderer() 
{
    //delete _triangleMesh;


    _triangleVertices.clear();


    for (MyMesh* mesh : _renderables)
        delete mesh; //delete pointers.
    _renderables.clear();

    delete _fontRenderer;

}

void MyRenderer::InitGL()
{
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);


}


void MyRenderer::InitTriangles(int triCount)
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
    float pos = 0.06f;

    for (int i = 0; i < triangleMeshCount; i++)
    {
        MyMesh* triangleMesh = new MyMesh(_triangleVertices); 
        triangleMesh->_tPosition = glm::vec3(pos, 0.0f, pos);
        AddMesh(triangleMesh);
        pos += 0.06f; 
    }
}

void MyRenderer::AddMesh(MyMesh* mesh)
{
    _renderables.push_back(mesh);
}

void MyRenderer::Update(float deltaTime)
{

    //Removed for mouse input update changes.
    //_camera.SetPosition(glm::vec3(0.0f, 0.1f, 2.0f));      
    //_camera.SetYawPitch(-90.0f, 0.0f);                   

    for (MyMesh* mesh : _renderables)
        mesh->Update(deltaTime);
}

void MyRenderer::Draw(float fps, float mouseX, float mouseY)
{
    //glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _shader->Use();


    _shader->SetMat4("u_View", _camera.GetViewMatrix());
    _shader->SetMat4("u_Projection", _camera.GetProjectionMatrix());

    for (MyMesh* mesh : _renderables)
    {
        mesh->Draw(*_shader);
    }


    _fpsText = "FPS: " + std::to_string(int(fps));
    _fontRenderer->RenderText(_fpsText, 15, 30, 1.0f, glm::vec3(1, 1, 1));

    _mouseClickPosText = "Mouse X " + std::to_string(int(mouseX)) + " Y " + std::to_string(int(mouseY));
    _fontRenderer->RenderText(_mouseClickPosText, 15, 490, 0.75f, glm::vec3(1, 1, 0));
}


void MyRenderer::Render(float deltaTime, float fps, float mouseX, float mouseY)
{

    Update(deltaTime);
    Draw(fps, mouseX, mouseY);

}

