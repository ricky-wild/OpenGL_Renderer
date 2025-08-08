#include "MyTextureManager.h"




std::unordered_map<std::string, GLuint> MyTextureManager::s_TextureCache;

GLuint MyTextureManager::GetTexture(const std::string& filePath)
{
    //If texture exists, reuse it to conserve memory.
    auto it = s_TextureCache.find(filePath);
    if (it != s_TextureCache.end())
    {
        return it->second; //Return texture ID.
    }

    //Otherwise, better load it from disk bro.
    GLuint textureID = LoadTextureFromFile(filePath);
    if (textureID != 0)
    {
        s_TextureCache[filePath] = textureID;
    }
    return textureID;
}

GLuint MyTextureManager::LoadTextureFromFile(const std::string& filePath)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true); //OpenGL expects bottom-left origin
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

    if (!data)
    {
        std::cerr << "Failed to load texture bro. MyTextureManager::LoadTextureFromFile() " << filePath << "\n";
        return 0;
    }

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    //Set texture filtering & wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data); //Free the CPU memory.

    return textureID;
}

void MyTextureManager::Clear()
{
    for (auto& pair : s_TextureCache)
    {
        glDeleteTextures(1, &pair.second);
    }
    s_TextureCache.clear();
}