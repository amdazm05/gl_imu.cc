#ifndef _VERTEX_BUFFER
#define _VERTEX_BUFFER

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <conversions/space_vector_units.hpp>
#include <buffer/buffer.hpp>
namespace Buffer
{
    class VertexBuffer : public Buffer::IBuffer<VertexBuffer>
    {
        public:
            VertexBuffer(std::shared_ptr<GladGLContext> windowContext);
            ~VertexBuffer();
            void init();
            void bind();
            void unbind();
        private:
            std::vector<Coordinates> _vertices;
    };
}

#endif //_VERTEX_BUFFER