#include "shader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

Renderer::Shader::Shader(std::string vertexPath, std::string fragmentPath){

    // retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // read file’s buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // close file handlers
        vShaderFile.close();
        fShaderFile.close();

        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    // print compile errors
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
    };

    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    // print compile errors
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << "\n";
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
    }

    // delete shaders; they’re linked into our program and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    glUseProgram(ID);
    
}

void Renderer::Shader::use(){
    glUseProgram(ID);
}

GLint Renderer::Shader::getLocation(const std::string &name) {
    if (cache.find(name) != cache.end())
        return cache[name];
    GLint location = glGetUniformLocation(ID, name.c_str());
    cache[name] = location;
    return location;
}

void Renderer::Shader::setBool(const std::string &name, bool value) {
    glUniform1i(getLocation(name), (int)value); 
}
void Renderer::Shader::setInt(const std::string &name, int value){ 
    glUniform1i(getLocation(name), value); 
}
void Renderer::Shader::setFloat(const std::string &name, float value) { 
    glUniform1f(getLocation(name), value); 
}
void Renderer::Shader::setVec2(const std::string &name, const glm::vec2 &value) { 
    glUniform2fv(getLocation(name), 1, &value[0]); 
}
void Renderer::Shader::setVec3(const std::string &name, const glm::vec3 &value) { 
    glUniform3fv(getLocation(name), 1, &value[0]); 
}
void Renderer::Shader::setVec4(const std::string &name, const glm::vec4 &value) { 
    glUniform4fv(getLocation(name), 1, &value[0]); 
}
void Renderer::Shader::setMat2(const std::string &name, const glm::mat2 &mat) {
    glUniformMatrix2fv(getLocation(name), 1, GL_FALSE, &mat[0][0]);
}
void Renderer::Shader::setMat3(const std::string &name, const glm::mat3 &mat) {
    glUniformMatrix3fv(getLocation(name), 1, GL_FALSE, &mat[0][0]);
}
void Renderer::Shader::setMat4(const std::string &name, const glm::mat4 &mat) {
    glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, &mat[0][0]);
}