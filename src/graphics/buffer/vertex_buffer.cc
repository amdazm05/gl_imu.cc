#include "graphics/buffer/vertex_buffer.hpp"

namespace Buffer
{
    VertexBuffer::VertexBuffer(std::shared_ptr<GladGLContext> windowContext): IBuffer<VertexBuffer>(windowContext)
    {

    }

    VertexBuffer::~VertexBuffer()
    {

    }

    void VertexBuffer::setData(std::vector<SpaceUnits::Coordinates<float>> && data)
    {
        // moved //Debug and see this more clearly
        _data = data;
    }

    void VertexBuffer::init()
    {   
        _windowContext->BindBuffer(GL_ARRAY_BUFFER,_id);
        _windowContext->BufferData(
            GL_ARRAY_BUFFER,
            _data.size()*sizeof(SpaceUnits::Coordinates<float>),
            nullptr,
            GL_STATIC_DRAW);
        _windowContext->BufferSubData(
            GL_ARRAY_BUFFER,0,
            _data.size()*sizeof(SpaceUnits::Coordinates<float>),
            &_data[0]);
    }

    void VertexBuffer::bind()
    {
        _windowContext->BindBuffer(GL_ARRAY_BUFFER,_id);
    }

    void VertexBuffer::unbind()
    {
        _windowContext->BindBuffer(GL_ARRAY_BUFFER,0);
    }
}