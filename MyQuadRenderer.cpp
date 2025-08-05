#include "MyQuadRenderer.h"
#include "stb_image.h"


#ifdef _DEBUG
const char* MyQuadRenderer::_sTextureVertShaderPathStr = "x64/Debug/shaders/texture.vert";
const char* MyQuadRenderer::_sTextureFragShaderPathStr = "x64/Debug/shaders/texture.frag";
const char* MyQuadRenderer::_sTextureFilePathStr = "x64/Debug/textures/tex.png";
#else
const char* MyQuadRenderer::_sTextureVertShaderPathStr = "shaders/texture.vert";
const char* MyQuadRenderer::_sTextureFragShaderPathStr = "shaders/texture.frag";
const char* MyQuadRenderer::_sTextureFilePathStr = "textures/tex.png";
#endif



MyQuadRenderer::MyQuadRenderer(MyWindow& window, float FOV, float FAR) : _camera(FOV, _renderViewWidth / _renderViewHeight, 0.1f, FAR) // fov, aspect, near, far
{
    glfwMakeContextCurrent(window.GetGLFWwindow());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    //glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    //glEnable(GL_DEPTH_TEST);

    _shader = new MyShader(_sTextureVertShaderPathStr, _sTextureFragShaderPathStr);
    InitQuad(); 

}

MyQuadRenderer::~MyQuadRenderer()
{

    for (MyMesh* mesh : _renderables)
        delete mesh; //delete pointers.
    _renderables.clear();


}

void MyQuadRenderer::InitQuad()
{
    float vertSize = 0.75f;

    //Define 6 vertices -2 triangles- with corresponding UVs
    std::vector<float> fullVerts = 
    {
        -vertSize,  vertSize, 0.0f,  //top left
         vertSize,  vertSize, 0.0f,  //top right
         vertSize, -vertSize, 0.0f,  //bottom right

         vertSize, -vertSize, 0.0f,  //bottom right
        -vertSize, -vertSize, 0.0f,  //bottom left
        -vertSize,  vertSize, 0.0f   //top left
    };

    std::vector<float> fullTex = 
    {
        0.0f, 1.0f,  //top left
        1.0f, 1.0f,  //top right
        1.0f, 0.0f,  //bottom right

        1.0f, 0.0f,  //bottom right
        0.0f, 0.0f,  //bottom left
        0.0f, 1.0f   //top left
    };

    unsigned int texID = LoadTexture(_sTextureFilePathStr);

    std::cout << "Texture ID: " << texID << "\n";


    MyMesh* texturedQuad = new MyMesh(fullVerts, fullTex, RenderMode::Textured);
    texturedQuad->SetTexture(texID);

    AddMesh(texturedQuad);


}

void MyQuadRenderer::AddMesh(MyMesh* mesh)
{
    _renderables.push_back(mesh);
}

void MyQuadRenderer::Update(float deltaTime)
{

    for (MyMesh* mesh : _renderables)
        mesh->Update(deltaTime);

    _camera.Update(deltaTime);
}

void MyQuadRenderer::Draw()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glDisable(GL_CULL_FACE);





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

void MyQuadRenderer::Render(float deltaTime)
{

    Update(deltaTime);
    Draw();

}

unsigned int MyQuadRenderer::LoadTexture(const std::string& path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture at: " << path << std::endl;
        return 0;
    }

    GLenum format = GL_RGB;
    if (nrChannels == 4) format = GL_RGBA;
    else if (nrChannels == 1) format = GL_RED;

    glBindTexture(GL_TEXTURE_2D, textureID);

    // Internal format (2nd arg) and format (7th arg) should match
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    // Unbind texture after setup (optional but clean)
    glBindTexture(GL_TEXTURE_2D, 0);

    std::cout << "Loaded texture: " << path
        << " (" << width << "x" << height << "), channels: " << nrChannels
        << ", ID: " << textureID << std::endl;

    return textureID;
}
