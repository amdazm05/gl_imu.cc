#ifndef _BUFFER
#define _BUFFER
#include <memory>

namespace Buffer
{
    //CRTP styled interface
    template<class _bufferType> 
    class IBuffer :  std::enable_shared_from_this<IBuffer>
    {
        public:
            IBuffer(std::shared_ptr<GladGLContext> windowContext)
            {
                _windowContext = windowContext;
            }
            ~IBuffer()
            {

            }
            void init()
            {
                static_cast<_bufferType *>(this)->init();   
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
                static_cast<_bufferType *>(this)->unbind(); 
            }
        private:
            std::shared_ptr<GladGLContext> _windowContext;
            uint _id;
    };
}

#endif