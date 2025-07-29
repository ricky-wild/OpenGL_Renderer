#include "MyShader.h"
#include <glm/gtc/type_ptr.hpp>

MyShader::MyShader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexCode = LoadShaderSource(vertexPath);
    std::string fragmentCode = LoadShaderSource(fragmentPath);

    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

    _id = LinkProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

MyShader::~MyShader()
{
    glDeleteProgram(_id);
}

unsigned int MyShader::GetID() const
{
    return _id;
}

void MyShader::Use() const
{
    glUseProgram(_id);//GetID());//_id);
}

void MyShader::SetMat4(const std::string& name, const glm::mat4& matrix) const
{
    int location = glGetUniformLocation(_id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void MyShader::SetVec3(const std::string& name, const glm::vec3& value) const
{
    int location = glGetUniformLocation(_id, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
}

std::string MyShader::LoadShaderSource(const std::string& filePath)
{
    std::ifstream file(filePath);
    std::stringstream buffer;

    if (!file.is_open())
    {
        std::cerr << "Failed to open shader file bro: MyShader::LoadShaderSource()" << filePath << std::endl;
        return "";
    }

    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int MyShader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader linking failed dude: MyShader::CompileShader()\n" << infoLog << std::endl;
    }

    return shader;
}

unsigned int MyShader::LinkProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Shader linking failed dude: MyShader::LinkProgram()\n" << infoLog << std::endl;
        throw std::runtime_error("Shader linking has failed pal, time to do some digging.");
    }
    else
    {
        std::cerr << "Shader linking was successful bro!\n" << std::endl;
    }

    return program;
}