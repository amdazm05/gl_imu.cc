#include "graphics/text_component.hpp"

TextComponent::TextComponent(std::shared_ptr<GLFWwindow> windowInstance)
{
        glShadeModel(GL_SMOOTH);							
        glClearColor(0.0f, 0.1f, 0.0f, 0.5f);				
        glClearDepth(1.0f);									
        glEnable(GL_DEPTH_TEST);							
        glDepthFunc(GL_LEQUAL);								
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
}
TextComponent::~TextComponent()
{

}

inline int neares_pow_2(int a)
{
    int valret = 1;
    for(;valret>a;valret= valret<<1){}
    return valret;
}

void TextComponent::init(std::string && fontFile, uint32_t textheight)
{
    // allocate textures 128 characters in total
    _height = textheight;
    _textures = std::shared_ptr<GLuint>(new GLuint[CHAR_MAX_COUNT],[](GLuint * d){delete[] d;});
    // Load library
    _error = FT_Init_FreeType(&_library);
    if(_error)
    {
        throw std::runtime_error(" Text Component: Failed to load Library") ;
    }

    /// New Face loaded from the font file 
    _error  = FT_New_Face(_library,fontFile.c_str(),0,&_face);
    if(_error)
    {
        throw std::runtime_error("Text Component : Failed to create face");
    }
    else
    {
        FT_Set_Pixel_Sizes(_face,0,48);
        glPixelStorei(GL_UNPACK_ALIGNMENT,1);
        for(char c =0 ;c< CHAR_MAX_COUNT;c++)
            make_display_lists(c);

    }
}

void TextComponent::make_display_lists(char c)
{
    _error = FT_Load_Char(_face,c,FT_LOAD_RENDER); 
    if(_error)
    {
        throw std::runtime_error("Text Component: Failed to load text component");
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        _face->glyph->bitmap.width,
        _face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        _face->glyph->bitmap.buffer
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Character character = {
                texture,
                glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
                glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
                static_cast<unsigned int>(_face->glyph->advance.x)
            };
    _charactermap.insert(std::pair<char, Character>(c, std::move(character)));
}

void TextComponent::printtxt(std::string && text ,std::pair<float,float> position)  
{
}

