#pragma once
#include "Common.h"


class MyTextureManager
{
    public:

        static GLuint GetTexture(const std::string& filePath);

        static void Clear();

    private:
        static std::unordered_map<std::string, GLuint> s_TextureCache;

        static GLuint LoadTextureFromFile(const std::string& filePath);
};