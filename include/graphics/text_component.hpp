#ifndef _TEXTCOMPONENT
#define _TEXTCOMPONENT

#include <GL/freeglut.h>
#include <GL/gl.h>
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
        void init(std::string && fontFile, uint32_t textheight);
        void printtxt(std::string && text, std::pair<float, float> position);
        std::shared_ptr<TextComponent> getInstance();
    private:
        /// @brief 
        // generates a display list in GL for a single character
        void make_display_lists(char character, FT_Face faceCpy);

        function_utils::function_ptr<void(*)(GLFWwindow* window, unsigned int codepoint)> _characterCallback;
        /// @brief each library is independant from oneanother, root of fonts, faces, size
        FT_Library _library;
        /// @brief face stores font information handle is required
        FT_Face _face;
        /// @brief is a number of the contiguou lists returned by GL allocation
        GLuint _listbase;
        std::shared_ptr<GLuint> _textures;
        std::shared_ptr<GLFWwindow> _windowContext;
        uint32_t _textheight;
        
        //font height
        float _height;

        //Glyph and bitmap members
        FT_Glyph _glyph;
        //Bit Map
        FT_BitmapGlyph _bitmapGlyph;
        FT_Bitmap _bitmap;
        //Allocates memory for each bitmap when characters are initialised
        std::shared_ptr<GLubyte> _expanded_bitmapdata; 

        
        //Error handling // Will be used for exceptions
        FT_Error _error;
        
        // Max character count
        static constexpr uint8_t CHAR_MAX_COUNT = 128;
    public:
        friend int neares_pow_2(int a);

};

#endif //_TEXTCOMPONENT


//Continue reading https://www.sccs.swarthmore.edu/users/03/sven/freetype_tut/