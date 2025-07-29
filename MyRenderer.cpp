
#include "MyRenderer.h"




MyRenderer::MyRenderer(MyWindow& window) : _camera(45.0f, _renderViewWidth / _renderViewHeight, 0.1f, 100.0f) // fov, aspect, near, far
{
    glfwMakeContextCurrent(window.GetGLFWwindow());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    InitGL();

    //_shader = new MyShader("x64/Debug/shaders/basic.vert", "x64/Debug/shaders/basic.frag");
    _shader = new MyShader("shaders/basic.vert", "shaders/basic.frag");  
    InitTriangle();


    unsigned int w = 512;
    unsigned int h = 512;

    //MyShader* textShader = new MyShader("x64/Debug/shaders/TextShader.vert", "x64/Debug/shaders/TextShader.frag");
    MyShader* textShader = new MyShader("shaders/TextShader.vert", "shaders/TextShader.frag");
    std::cerr << "Text shader successfully loaded man!\n";

    _fontRenderer = new MyBitmapFontRenderer(textShader, w, h);
    std::cerr << "Font renderer successfully initialized bro!\n";

    //_fontRenderer->LoadFontTexture("x64/Debug/textures/font_atlas_01.png");
    _fontRenderer->LoadFontTexture("textures/font_atlas_01.png");
    std::cerr << "Font texture successfully loaded dude!\n";

    _fontRenderer->RenderText("Hello", 15, 30, 0.5f, glm::vec3(1, 1, 0));
    std::cerr << "RenderText successfully called!\n";
}

MyRenderer::~MyRenderer() 
{
    //delete _triangleMesh;


    _triangleVertices.clear();

    for (MyMesh* mesh : _renderables)
        delete mesh;
    _renderables.clear();

    delete _fontRenderer;
}

void MyRenderer::InitGL()
{
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);

}


void MyRenderer::InitTriangle()
{
    float vertPos = 0.15f;

    //Simple triangle, 3 verts with x, y and z.
    _triangleVertices =
    {
         0.0f,  vertPos, 0.0f,      // top
        -vertPos, -vertPos, 0.0f,   // bottom-left
         vertPos, -vertPos, 0.0f    // bottom-right
    };

    //Create mesh and add it to _renderables.
    MyMesh* triangleMesh = new MyMesh(_triangleVertices);


    vertPos = 0.20f;

    MyMesh* triangleMesh2 = new MyMesh(_triangleVertices);
    triangleMesh2->_tPosition = glm::vec3(-0.4f);


    MyMesh* triangleMesh3 = new MyMesh(_triangleVertices);
    triangleMesh3->_tPosition = glm::vec3(0.4f);

    AddMesh(triangleMesh);
    AddMesh(triangleMesh2);
    AddMesh(triangleMesh3);
}

void MyRenderer::Update(float deltaTime)
{


    _camera.SetPosition(glm::vec3(0.0f, 0.1f, 2.0f));      
    _camera.SetYawPitch(-90.0f, 0.0f);                   

    for (MyMesh* mesh : _renderables)
        mesh->Update(deltaTime);
}

void MyRenderer::Draw(float fps)
{
    //glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _shader->Use();

    //glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    //glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    _shader->SetMat4("u_View", _camera.GetViewMatrix());
    _shader->SetMat4("u_Projection", _camera.GetProjectionMatrix());

    for (MyMesh* mesh : _renderables)
    {
        mesh->Draw(*_shader);
    }

    //_fontRenderer->RenderText("FPS:", 15, 30, 1.0f, glm::vec3(1, 1, 1));
    std::string fpsText = "FPS: " + std::to_string(int(fps));
    _fontRenderer->RenderText(fpsText, 15, 30, 1.0f, glm::vec3(1, 1, 1));
}


void MyRenderer::Render(float deltaTime, float fps)
{

    Update(deltaTime);
    Draw(fps);

}

void MyRenderer::AddMesh(MyMesh* mesh)
{
    _renderables.push_back(mesh);
}