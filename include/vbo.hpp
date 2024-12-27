#include <glad/glad.h>

namespace Renderer {
    class VBO {
    public:
        VBO(const void* data, unsigned int size);
        ~VBO();

        void bind();
        void unbind();
    private:

        GLuint ID;
    };
}