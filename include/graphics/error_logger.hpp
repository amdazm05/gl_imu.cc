#ifndef _ERROR_LOGGER
#define _ERROR_LOGGER

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <source_location>
#include <memory>
#include <fstream>

class GraphicsErrorHandler : std::enable_shared_from_this<GraphicsErrorHandler> 
{
    public:
        GraphicsErrorHandler(std::string && errorFilename, std::shared_ptr<GladGLContext> windowContext);
        ~GraphicsErrorHandler();
        void LogErrors(const std::source_location location  = std::source_location::current());
    private:
        GLenum _err; 
        std::fstream _errorFilep;
}

#endif //_ERROR_LOGGER