
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

//const char* MyRenderer::_sBasicVertShaderPathStr = "shaders/basic.vert";
//const char* MyRenderer::_sBasicFragShaderPathStr = "shaders/basic.frag";
//const char* MyRenderer::_sTextVertShaderPathStr = "shaders/TextShader.vert";
//const char* MyRenderer::_sTextFragShaderPathStr = "shaders/TextShader.frag";
//const char* MyRenderer::_sFontShaderPathStr = "textures/font_atlas_01.png";


const int TRI_COUNT = 1000;




MyRenderer::MyRenderer(MyWindow& window) : _camera(45.0f, _renderViewWidth / _renderViewHeight, 0.1f, 250.0f) // fov, aspect, near, far
{
    glfwMakeContextCurrent(window.GetGLFWwindow());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    InitGL();

    _shader = new MyShader(_sBasicVertShaderPathStr, _sBasicFragShaderPathStr);
    InitTriangles(TRI_COUNT);


    unsigned int w = 800;
    unsigned int h = 600;

    MyShader* textShader = new MyShader(_sTextVertShaderPathStr, _sTextFragShaderPathStr);
    std::cerr << "Text shader successfully loaded man!\n";

    _fontRenderer = new MyBitmapFontRenderer(textShader, w, h);
    std::cerr << "Font renderer successfully initialized bro!\n";

    _fontRenderer->LoadFontTexture(_sFontShaderPathStr);
    std::cerr << "Font texture successfully loaded dude!\n";

    _fontRenderer->RenderText("Hello", 15, 30, 0.5f, glm::vec3(1, 1, 0));
    std::cerr << "RenderText successfully called!\n";

    _camera.SetPosition(glm::vec3(0.0f, 0.1f, 2.0f));
    _camera.SetYawPitch(90.0f, 0.0f);
}

MyRenderer::~MyRenderer() 
{

    _triangleVertices.clear();


    for (MyMesh* mesh : _renderables)
        delete mesh; //delete pointers.
    _renderables.clear();

    delete _fontRenderer;

}

void MyRenderer::InitGL()
{

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
    float x = 0.1f;
    float y = 0.03f;
    float z = 0.05f;

    for (int i = 0; i < triangleMeshCount; i++)
    {
        MyMesh* triangleMesh = new MyMesh(_triangleVertices); 
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

    //float vertPos = 0.075f;
    //std::vector<float> vertices;
    //vertices.reserve(triCount * 3 * 3); // 3 vertices per triangle, 3 floats per vertex

    //float x = 0.0f;
    //float y = 0.0f;
    //float z = 0.0f;

    //for (int i = 0; i < triCount; ++i)
    //{
    //    // Triangle vertices offset by position
    //    vertices.push_back(x + 0.0f);       vertices.push_back(y + vertPos); vertices.push_back(z + 0.0f);
    //    vertices.push_back(x - vertPos);    vertices.push_back(y - vertPos); vertices.push_back(z + 0.0f);
    //    vertices.push_back(x + vertPos);    vertices.push_back(y - vertPos); vertices.push_back(z + 0.0f);

    //    // Change position for next triangle
    //    x += 0.1f;
    //    y += (i <= triCount / 2) ? 0.01f : -0.01f;
    //    z -= 0.1f;
    //}

    //_totalVertices = triCount * 3;

    //// Create and bind VAO and VBO
    //glGenVertexArrays(1, &_batchVAO);
    //glGenBuffers(1, &_batchVBO);

    //glBindVertexArray(_batchVAO);
    //glBindBuffer(GL_ARRAY_BUFFER, _batchVBO);
    //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    //// Setup vertex attrib pointer
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    //// Unbind VAO
    //glBindVertexArray(0);
}

void MyRenderer::AddMesh(MyMesh* mesh)
{
    _renderables.push_back(mesh);
}

void MyRenderer::Update(float deltaTime)
{             

    for (MyMesh* mesh : _renderables)
        mesh->Update(deltaTime);

    _camera.Update(deltaTime);
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

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //_shader->Use();

    //_shader->SetMat4("u_View", _camera.GetViewMatrix());
    //_shader->SetMat4("u_Projection", _camera.GetProjectionMatrix());

    //glBindVertexArray(_batchVAO);

    //_shader->SetMat4("u_Model", glm::mat4(1.0f));

    //glDrawArrays(GL_TRIANGLES, 0, _totalVertices);

    //glBindVertexArray(0);



    _fpsText = "FPS: " + std::to_string(int(fps));
    _fontRenderer->RenderText(_fpsText, 15, 30, 1.0f, glm::vec3(1, 1, 1));

    _mouseClickPosText = "Mouse X " + std::to_string(int(mouseX)) + " Y " + std::to_string(int(mouseY));
    _fontRenderer->RenderText(_mouseClickPosText, 15, 570, 0.75f, glm::vec3(1, 1, 0));

    _trisRenderedCountText = "Trangles Rendered " + std::to_string(int(TRI_COUNT));
    _fontRenderer->RenderText(_trisRenderedCountText, 15, 550, 0.75f, glm::vec3(0, 1, 0));
}


void MyRenderer::Render(float deltaTime, float fps, float mouseX, float mouseY)
{

    Update(deltaTime);
    Draw(fps, mouseX, mouseY);

}

