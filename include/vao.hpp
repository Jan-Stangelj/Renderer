#include <glad/glad.h>

#include <vector>

// index size type normalized stride (void*)0

namespace Renderer {

    struct vertexAttribute {
        GLuint index;
        GLint size;
        GLenum type;
        GLboolean normalized;
        GLsizei stride;

        vertexAttribute(GLuint idx, GLint s, GLenum t, GLboolean n, GLsizei str)
        : index(idx), size(s), type(t), normalized(n), stride(str) {}
    };

    class VAO {
    public:
        VAO();
        ~VAO();

        void addAttribute(const vertexAttribute &Attribute);

        void bind();
        void unbind();
    private:
        GLuint ID;
    };
}