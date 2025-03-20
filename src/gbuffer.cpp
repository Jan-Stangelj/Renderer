#include "gbuffer.hpp"


Renderer::gBuffer::gBuffer(unsigned int width, unsigned int height) {
    glGenFramebuffers(1, &ID);
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
    
    // - position color buffer
    gPosition.generateForFBO(width, height, GL_RGB16F, GL_RGB);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition.ID, 0);
    
    // - normal color buffer
    gNormal.generateForFBO(width, height, GL_RGB16F, GL_RGB);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal.ID, 0);
    
    // - color buffer
    gAlbedo.generateForFBO(width, height, GL_RGBA, GL_RGBA);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo.ID, 0);

    // - pbr buffer
    gPBR.generateForFBO(width, height, GL_RGB, GL_RGB);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, gPBR.ID, 0);

    // - emission
    gEmission.generateForFBO(width, height, GL_RGB, GL_RGB);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, gEmission.ID, 0);

    // - tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
    unsigned int attachments[5] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4};
    glDrawBuffers(5, attachments);

    // create and attach depth buffer (renderbuffer)
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1280, 720);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

Renderer::gBuffer::~gBuffer() {
    glDeleteFramebuffers(1, &ID);
}

void Renderer::gBuffer::bindFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void Renderer::gBuffer::unbindFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::gBuffer::bindTextures(Renderer::Shader shader) {
    gAlbedo.Bind(0, shader, "gAlbedo");
    gPosition.Bind(1, shader, "gPosition");
    gNormal.Bind(2, shader, "gNormal");
    gPBR.Bind(3, shader, "gPBR");
    gEmission.Bind(4, shader, "gEmission");
}

void Renderer::gBuffer::renderQuad() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    float quadVertices[] = {
        // positions        // texture Coords
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
        1.0f,  -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f
    };

    unsigned int quadVAO;
    unsigned int quadVBO;
    // setup plane VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);

    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STREAM_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDeleteBuffers(1, &quadVBO);
    glDeleteVertexArrays(1, &quadVAO);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}