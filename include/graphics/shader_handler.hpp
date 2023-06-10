#ifndef _SHADER_COMPILER
#define _SHADER_COMPILER

#include <memory>
#include <istream>

class ShaderHandler : std::enable_shared_from_this<ShaderHandler>
{
    public:
        ShaderHandler(
            std::string && vertexShaderSourcePath,
            std::string && fragmentShaderSourcePath,
            std::string && geometryShaderSourcePath = nullptr
        );
        ~ShaderHandler();
        // required for context sharing
        std::shared_ptr<ShaderHandler> getInstance();
        uint32_t getShaderId();
        void useProgram() noexcept;
        void generateShaders() noexcept;

        // Logging Errorss
        std::string getCompileLog();
        std::string getLinklog();
        void setErrorLogging(bool statuss);

    private:
        //Generate shaders will generate use the two
        uint32_t compileShaders() noexcept;
        uint32_t linkShaders() noexcept;
        std::istream _vertexShaderFileHandle; 
        std::istream _fragmentShaderFileHandle;
        std::uint32_t _shaderId;
};

#endif //_SHADER_COMPILER