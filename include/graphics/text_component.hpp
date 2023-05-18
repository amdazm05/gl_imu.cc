#ifndef _TEXTCOMPONENT
#define _TEXTCOMPONENT

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H  
#include <memory>
#include <unordered_map>
#include <string>

#include "util/functionutils.tpp"

class TextComponent : std::enable_shared_from_this<TextComponent>
{
    public:
        TextComponent(std::shared_ptr<GLFWwindow> windowInstance);
        TextComponent() = delete;
        ~TextComponent();
        void renderText(std::string && inputText,std::pair<double,double> renderPosition,std::tuple<uint8_t,uint8_t,uint8_t> color);
        std::shared_ptr<TextComponent> getInstance();

    private:
        function_utils::function_ptr<void(*)(GLFWwindow* window, unsigned int codepoint)> _characterCallback;
        std::unordered_map<GLchar,char> _gltocharMap;
        std::shared_ptr<GLFWindow> _windowContext;
};

#endif //_TEXTCOMPONENT