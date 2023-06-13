#include "graphics/shader_handler.hpp"

#define FILE_ALLOCATOR(filename) new std::ifstream(filename, std::ios_base::in)
#define FILE_DELETER [](std::ifstream * fileHandle){ fileHandle->close(); delete [] fileHandle;}

ShaderHandler::ShaderHandler
(
    std::string && vertexShaderSourcePath,
    std::string && fragmentShaderSourcePath,
    std::string && geometryShaderSourcePath,
    std::shared_ptr<GladGLContext> windowContext
):
 _fragmentShaderFileHandle(FILE_ALLOCATOR(fragmentShaderSourcePath),FILE_DELETER),
 _vertexShaderFileHandle(FILE_ALLOCATOR(vertexShaderSourcePath),FILE_DELETER),
 _windowContext(windowContext)
{

    //TODO once we get there :)
    if(geometryShaderSourcePath.c_str()!=nullptr)
    {
        //Open file else do nothing
    }
    else
    {
        
    }


}

void ShaderHandler::generateShaderProgram() noexcept
{
    if(_fragmentShaderFileHandle->is_open() && _vertexShaderFileHandle->is_open())
    {
        *_fragmentShaderFileHandle  >>_vertSh;
        *_vertexShaderFileHandle    >>_fragSh;
    }
    
    if(_vertSh.c_str()!=nullptr && _fragSh.c_str()!=nullptr)
    {
        // Create Shaders
        _vertex   = _windowContext->CreateShader(GL_VERTEX_SHADER);
        _fragment = _windowContext->CreateShader(GL_FRAGMENT_SHADER);
        compileShaders();
        linkShaders();
    }

}

inline uint32_t ShaderHandler::compileShaders() noexcept
{
    const char * vertSh = _vertSh.c_str();
    _windowContext->ShaderSource(_vertex, 1,   &(vertSh) , NULL);
    _windowContext->CompileShader(_vertex);
    checkForCompileErrors();
    
    const char * fragSh = _fragSh.c_str();
    _windowContext->ShaderSource(_fragment, 1,   &(fragSh) , NULL);
    _windowContext->CompileShader(_fragment);
    checkForCompileErrors();
}

inline void ShaderHandler::checkForCompileErrors()
{
    GLint success;
    GLchar infoLog[1024];
    _windowContext->GetShaderiv(_shaderId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        _windowContext->GetShaderInfoLog(_shaderId, 1024, NULL, infoLog);
        _compileStatus = infoLog;
    }
}

inline void ShaderHandler::checkForLinkErrors()
{
    GLint success;
    GLchar infoLog[1024];
    _windowContext->GetProgramiv(_shaderId, GL_LINK_STATUS, &success);
    if(!success)
    {
        _windowContext->GetProgramInfoLog(_shaderId, 1024, NULL, infoLog);
    }
}

inline uint32_t ShaderHandler::linkShaders() noexcept
{
    _shaderId = _windowContext->CreateProgram();
    _windowContext->AttachShader(_shaderId, _vertex);
    _windowContext->AttachShader(_shaderId, _fragment);
    _windowContext->LinkProgram(_shaderId);
}

inline std::string ShaderHandler::getCompileLog()
{
    return _compileStatus;
}
inline std::string ShaderHandler::getLinklog()
{
    return _linkStatus;
}

void ShaderHandler::useProgram() noexcept
{
    _windowContext->UseProgram(_shaderId);
}

ShaderHandler::~ShaderHandler()
{

}