#include "graphics/error_logger.hpp"

#define ERROR_FILE_ALLOCATOR(filename) new std::fstream(filename, std::ios_base::out | std::ios_base::app)
#define ERROR_FILE_DELETER [](std::fstream * fileHandle){ fileHandle->close();}

//Opens file and allows read and write
GraphicsErrorHandler::GraphicsErrorHandler(std::string && errorFilename, std::shared_ptr<GladGLContext> windowContext)
:   _errorFilep(ERROR_FILE_ALLOCATOR(errorFilename),ERROR_FILE_DELETER), _windowContext(windowContext)
{

}
GraphicsErrorHandler::~GraphicsErrorHandler()
{
    //Destructor
}
void GraphicsErrorHandler::LogErrors(const std::source_location location  )
{
    _err = _windowContext->GetError();
    if(!_err)
    {

    }
    else
    {
        _now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(_now);
    
        (*_errorFilep) <<"["<<std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X")<<"]"
        << location.file_name() << '('
        << location.line() << ':'
        << location.column() << ") `"
        << location.function_name() << "`: "
         <<" Graphics - OpenGL Error num: " << _err << "\n";
        
        (*_errorFilep).flush();
    }
}