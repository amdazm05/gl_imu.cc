#include "graphics/shader_handler.hpp"

#define FILE_ALLOCATOR(filename) new std::ifstream(filename, std::ios_base::in)
#define FILE_DELETER [](std::ifstream * fileHandle){ fileHandle->close();}

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
    std::stringstream bufferStream;
    if(_fragmentShaderFileHandle->is_open() && _vertexShaderFileHandle->is_open())
    {
        bufferStream << (*_fragmentShaderFileHandle).rdbuf();
        _fragSh.append(bufferStream.str());
        bufferStream.str("");
        bufferStream << (*_vertexShaderFileHandle).rdbuf();
        _vertSh.append(bufferStream.str());
        bufferStream.str("");
    }
    if(_vertSh.c_str()!=nullptr && _fragSh.c_str()!=nullptr)
    {
        // Create Shaders
        _vertex   = _windowContext->CreateShader(GL_VERTEX_SHADER);
        _fragment = _windowContext->CreateShader(GL_FRAGMENT_SHADER);
        compileShaders();
        linkShaders();

        _windowContext->DeleteShader(_vertex);
        _windowContext->DeleteShader(_fragment);
    }

}

inline uint32_t ShaderHandler::compileShaders() noexcept
{
    const char * vertSh = _vertSh.c_str();
    std::cout<<vertSh<<std::endl;
    _windowContext->ShaderSource(_vertex, 1,   &(vertSh) , NULL);
    _windowContext->CompileShader(_vertex);
    checkForCompileErrors(_vertex);
    
    const char * fragSh = _fragSh.c_str();
    std::cout<<fragSh<<std::endl;
    _windowContext->ShaderSource(_fragment, 1,   &(fragSh) , NULL);
    _windowContext->CompileShader(_fragment);
    checkForCompileErrors(_fragment);
    return {};
}

inline void ShaderHandler::checkForCompileErrors(uint32_t shader)
{
    GLint success;
    GLchar infoLog[1024];
    _windowContext->GetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        _windowContext->GetShaderInfoLog(shader, 1024, NULL, infoLog);
        _compileStatus = infoLog;
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: "<< "\n" << _compileStatus << "\n -- --------------------------------------------------- -- " << std::endl;
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
        std::cout<<infoLog<<std::endl;
    }
}

inline uint32_t ShaderHandler::linkShaders() noexcept
{
    _shaderId = _windowContext->CreateProgram();
    _windowContext->AttachShader(_shaderId, _vertex);
    _windowContext->AttachShader(_shaderId, _fragment);
    _windowContext->LinkProgram(_shaderId);
    return {};
}

std::string ShaderHandler::getCompileLog()
{
    return _compileStatus;
}
std::string ShaderHandler::getLinklog()
{
    return _linkStatus;
}

void ShaderHandler::useProgram() noexcept
{
    _windowContext->UseProgram(_shaderId);
}

GLuint ShaderHandler::getShaderId()
{
    return _shaderId;
}

ShaderHandler::~ShaderHandler()
{

}