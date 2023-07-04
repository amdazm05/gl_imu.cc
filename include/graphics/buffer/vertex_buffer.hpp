#ifndef _VERTEX_BUFFER
#define _VERTEX_BUFFER

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <vector>

#include <conversions/space_vector_units.hpp>
#include "buffer.hpp"
namespace Buffer
{
    class VertexBuffer : public Buffer::IBuffer<VertexBuffer>
    {
        public:
            VertexBuffer(std::shared_ptr<GladGLContext> windowContext);
            ~VertexBuffer();
            void setData(std::vector<SpaceUnits::Coordinates<float>> && data);
            void init();
            void bind();
            void unbind();
    };
}

#endif //_VERTEX_BUFFER