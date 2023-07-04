#ifndef _BUFFER
#define _BUFFER
#include <memory>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
namespace Buffer
{
    //CRTP styled interface
    template<class _bufferType> 
    class IBuffer :  std::enable_shared_from_this<IBuffer<_bufferType>>
    {
        public:
            IBuffer(std::shared_ptr<GladGLContext> windowContext)
            {
                _windowContext->GenBuffers(1,&_id);
                _windowContext = windowContext;
            }
            ~IBuffer()
            {
                //Unbinds and deletes buffers
                unbind();
                _windowContext->DeleteBuffers(1,&_id);
            }
            void init()
            {
                static_cast<_bufferType *>(this)->init();   
            }
            void setData(std::vector<SpaceUnits::Coordinates<float>> && data)
            {
                static_cast<_bufferType *>(this)->setData(data); 
            }
            void bind()
            {
                static_cast<_bufferType *>(this)->bind();   
            }
            void unbind()
            {   
                static_cast<_bufferType *>(this)->unbind();   
            }
            void getBufferId()
            {
                static_cast<_bufferType *>(this)->getBufferId(); 
            }
        protected:
            std::shared_ptr<GladGLContext> _windowContext;
            GLuint _id;
            // Could be vertices //fragments or anything else
            std::vector<SpaceUnits::Coordinates<float>> _data;
    };
}

#endif