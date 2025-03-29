#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Renderer::Texture::Texture(const std::string& file, bool linearColorSpace) {
    generate(file, linearColorSpace);
}
Renderer::Texture::~Texture() {
    glDeleteTextures(1, &ID);
}

void Renderer::Texture::generate(const std::string& file, bool linearColorSpace) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 16);


    // load and generate the texture
    int width, height, colorChannels;
    //stbi_set_flip_vertically_on_load(true);  
    unsigned char *data = stbi_load(file.c_str(), &width, &height, &colorChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB+colorChannels-3, width, height, 0, GL_RGB+colorChannels-3, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture\n";
    }
    stbi_image_free(data);
}

void Renderer::Texture::generateForFBO(unsigned int width, unsigned int height, GLint internalFormat, GLenum format) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Renderer::Texture::Bind(unsigned int textureUnit, Renderer::Shader &shader, const std::string& textureUniform) {
    shader.use();
    shader.setInt(textureUniform.c_str(), textureUnit);
    glActiveTexture(0x84C0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, ID);
}
void Renderer::Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}