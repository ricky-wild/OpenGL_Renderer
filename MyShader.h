
#pragma once
#include "Common.h"

class MyShader
{
    public:
        MyShader(const std::string& vertexPath, const std::string& fragmentPath);
        ~MyShader();

        void Use() const;

        void SetMat4(const std::string& name, const glm::mat4& matrix) const;

    private:
        unsigned int _id;

        std::string LoadShaderSource(const std::string& filePath);
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int LinkProgram(unsigned int vertexShader, unsigned int fragmentShader);
};
