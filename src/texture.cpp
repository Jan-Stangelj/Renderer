#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>
#include <unordered_map>

Renderer::Texture::Texture(std::string file, unsigned int textureUint, Renderer::Shader &shader, std::string textureUniform, unsigned int colorChannels) {

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char *data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);

    const GLenum lookup2[] = {0, 0, GL_RG, GL_RGB, GL_RGBA};

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, lookup2[colorChannels], GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture\n";
    }
    stbi_image_free(data);

    const GLenum lookup[] = {GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5, GL_TEXTURE6, GL_TEXTURE7, GL_TEXTURE8, GL_TEXTURE9, GL_TEXTURE10, GL_TEXTURE11, GL_TEXTURE12, GL_TEXTURE13, GL_TEXTURE14, GL_TEXTURE15};
    glActiveTexture(lookup[textureUint]);
    glBindTexture(GL_TEXTURE_2D, ID);
    shader.use();
    shader.setInt(textureUniform.c_str(), textureUint);
}
Renderer::Texture::~Texture() {
    glDeleteTextures(1, &ID);
}

void Renderer::Texture::Bind(unsigned int textureUint, Renderer::Shader &shader, std::string textureUniform) {
    const GLenum lookup[] = {GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5, GL_TEXTURE6, GL_TEXTURE7, GL_TEXTURE8, GL_TEXTURE9, GL_TEXTURE10, GL_TEXTURE11, GL_TEXTURE12, GL_TEXTURE13, GL_TEXTURE14, GL_TEXTURE15};
    glActiveTexture(lookup[textureUint]);
    glBindTexture(GL_TEXTURE_2D, ID);
    shader.use();
    shader.setInt(textureUniform.c_str(), textureUint);
}
void Renderer::Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}