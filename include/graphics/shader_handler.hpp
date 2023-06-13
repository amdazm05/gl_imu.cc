#ifndef _SHADER_COMPILER
#define _SHADER_COMPILER

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
class ShaderHandler : std::enable_shared_from_this<ShaderHandler>
{
    public:
        ShaderHandler(
            std::string && vertexShaderSourcePath,
            std::string && fragmentShaderSourcePath,
            std::string && geometryShaderSourcePath,
            std::shared_ptr<GladGLContext> windowContext
        );
        ~ShaderHandler();
        // required for context sharing
        std::shared_ptr<ShaderHandler> getInstance();
        void useProgram() noexcept;
        void generateShaderProgram() noexcept;

        // Logging Errorss
        std::string getCompileLog();
        std::string getLinklog();
        GLuint getShaderId();
        void setErrorLogging(bool statuss);

    private:
        //Generate shaders will generate use the two
        std::string _compileStatus;
        std::string _linkStatus;
        std::string _vertSh;
        std::string _fragSh;

        void checkForLinkErrors();
        void checkForCompileErrors(uint32_t shader);
        
        uint32_t compileShaders() noexcept;
        uint32_t linkShaders() noexcept;
        std::unique_ptr<std::ifstream,void(*)(std::ifstream *)> _vertexShaderFileHandle; 
        std::unique_ptr<std::ifstream,void(*)(std::ifstream *)> _fragmentShaderFileHandle;
        std::uint32_t _shaderId;
        std::shared_ptr<GladGLContext> _windowContext;
        unsigned int _vertex, _fragment;
};

#endif //_SHADER_COMPILER