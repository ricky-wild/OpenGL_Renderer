#include "MyGlyphRenderer.h"

#ifdef _DEBUG
const char* MyGlyphRenderer::_sTextVertShaderPathStr = "x64/Debug/shaders/TextShader.vert";
const char* MyGlyphRenderer::_sTextFragShaderPathStr = "x64/Debug/shaders/TextShader.frag";
const char* MyGlyphRenderer::_sFontShaderPathStr = "x64/Debug/textures/font_atlas_01.png";
#else
const char* MyGlyphRenderer::_sTextVertShaderPathStr = "shaders/TextShader.vert";
const char* MyGlyphRenderer::_sTextFragShaderPathStr = "shaders/TextShader.frag";
const char* MyGlyphRenderer::_sFontShaderPathStr = "textures/font_atlas_01.png";
#endif



MyGlyphRenderer::MyGlyphRenderer(MyWindow& window, float FOV, float FAR) : _camera(FOV, _renderViewWidth / _renderViewHeight, 0.1f, FAR) // fov, aspect, near, far
{
    glfwMakeContextCurrent(window.GetGLFWwindow());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    //glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    //glEnable(GL_DEPTH_TEST);

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



}

MyGlyphRenderer::~MyGlyphRenderer()
{

    delete _fontRenderer;

}



void MyGlyphRenderer::Draw(float fps, float mouseX, float mouseY, int triCount, int quadCount)
{
    //glClear(GL_COLOR_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    _fpsText = "FPS: " + std::to_string(int(fps));
    _fontRenderer->RenderText(_fpsText, 15, 30, 1.0f, glm::vec3(1, 1, 1));

    _mouseClickPosText = "Mouse X " + std::to_string(int(mouseX)) + " Y " + std::to_string(int(mouseY));
    _fontRenderer->RenderText(_mouseClickPosText, 15, 570, 0.75f, glm::vec3(1, 1, 0));

    _trisRenderedCountText = "Triangle-Mesh Rendered: " + std::to_string(triCount);
    _fontRenderer->RenderText(_trisRenderedCountText, 15, 550, 0.75f, glm::vec3(1, 0.6, 0.1));

    _quadRenderedCountText = "Textured Quad-Mesh Rendered: " + std::to_string(quadCount);
    _fontRenderer->RenderText(_quadRenderedCountText, 15, 530, 0.75f, glm::vec3(1, 0.6, 0));

    //_mouseControlHelpText
    _mouseControlHelpText = "Control Help: Mouse Wheel to ZOOM. Mouse Right Clickhold to ROTATE.";
    _fontRenderer->RenderText(_mouseControlHelpText, 15, 50, 0.75f, glm::vec3(1, 1, 1));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MyGlyphRenderer::Render(float deltaTime, float fps, float mouseX, float mouseY, int triCount, int quadCount)
{
    Draw(fps, mouseX, mouseY, triCount, quadCount);
}