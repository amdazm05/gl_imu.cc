#ifndef _TEXTCOMPONENT
#define _TEXTCOMPONENT

#include <glad/gl.h>
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
        void setTextFontProperties(std::uint8_t fontSize,std::string && fontInformation);
        void renderText(std::string && inputText,std::pair<double,double> renderPosition,std::tuple<uint8_t,uint8_t,uint8_t> color);
        std::shared_ptr<TextComponent> getInstance();

    private:
        void generateBitMapImage();
        void renderGlyph();
        function_utils::function_ptr<void(*)(GLFWwindow* window, unsigned int codepoint)> _characterCallback;
        std::unordered_map<GLchar,char> _gltocharMap;
        FT_Bitmap _bitmap; 
        FT_Library _library;
        FT_Face _face;
        FT_Error _errorhandle;
        std::unordered_map<char ,FT_UInt> _glyphIndexMap;
        std::shared_ptr<GLFWwindow> _windowContext;
};

#endif //_TEXTCOMPONENT