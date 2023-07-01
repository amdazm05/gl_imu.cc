#ifndef _VERTEX_BUFFER
#define _VERTEX_BUFFER

#include <glad/gl.h>
#include <GLFW/glfw3.h>
namespace Buffer
{
    class VertexBuffer : public Buffer<VertexBuffer>
    {
        public:
            VertexBuffer(shared_ptr<Glad>);
            ~VertexBuffer();
            void init();
            void bind();
            void unbind();
        private:
            std::vector</*Add coordinates Class*/> _vertices;
    };
}

#endif //_VERTEX_BUFFER