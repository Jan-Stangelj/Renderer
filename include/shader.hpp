#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <unordered_map>
#include <string>

namespace Renderer{
    class Shader{
    public:
        Shader(std::string vertexPath, std::string fragmentPath);

        void use();

        void setBool(const std::string &name, bool value);
        void setInt(const std::string &name, int value);
        void setFloat(const std::string &name, float value);
        void setVec2(const std::string &name, const glm::vec2 &value);
        void setVec3(const std::string &name, const glm::vec3 &value);
        void setVec4(const std::string &name, const glm::vec4 &value);
        void setMat2(const std::string &name, const glm::mat2 &mat);
        void setMat3(const std::string &name, const glm::mat3 &mat);
        void setMat4(const std::string &name, const glm::mat4 &mat);

    private:
        GLuint ID;
        std::unordered_map<std::string, GLint> cache;

        GLint getLocation(const std::string& name);
    };
}