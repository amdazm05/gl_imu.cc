#ifndef _TEXTCOMPONENT
#define _TEXTCOMPONENT

#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include FT_FREETYPE_H  
#include <memory>
#include <iostream>
#include <unordered_map>
#include <string>

#include "util/functionutils.tpp"

class TextComponent : std::enable_shared_from_this<TextComponent>
{
    public:
        TextComponent(std::shared_ptr<GLFWwindow> windowInstance);
        TextComponent() = delete;
        ~TextComponent();
        void init();
        void setTextFontProperties(std::uint8_t fontSize,std::string && fontInformation);
        void renderText(std::string && inputText,std::pair<double,double> renderPosition,std::tuple<uint8_t,uint8_t,uint8_t> color);
        std::shared_ptr<TextComponent> getInstance();

    private:
        void generateBitMapImage();
        void renderGlyph();
        function_utils::function_ptr<void(*)(GLFWwindow* window, unsigned int codepoint)> _characterCallback;
        FT_Bitmap _bitmap; 
        FT_Library _library;
        FT_Face _face;
        FT_Error _errorhandle;
        FT_Glyph _glyph;
        GLuint tex_handle;
        int tex_width = _bitmap.width;
        int tex_height = _bitmap.rows;
        std::unordered_map<char ,FT_UInt> _glyphIndexMap;
        std::shared_ptr<GLFWwindow> _windowContext;
};

#endif //_TEXTCOMPONENT


//Continue reading https://www.sccs.swarthmore.edu/users/03/sven/freetype_tut/