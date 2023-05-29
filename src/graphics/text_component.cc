#include "graphics/text_component.hpp"

TextComponent::TextComponent(std::shared_ptr<GLFWwindow> windowInstance)
{

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
    _textheight = textheight;
    FT_Set_Char_Size(_face, _textheight<<6, _textheight<<6, 96,96);

    // List base is the count of contiguous "empty" lists allocated by GL
    _listbase = glGenLists(CHAR_MAX_COUNT);

    // glGenTextures generates the unique names provided by GL taht are stored in textures
    if(_textures != nullptr)
        glGenTextures(CHAR_MAX_COUNT,_textures.get());
}

void TextComponent::make_display_lists(char character, FT_Face faceCpy)
{
    _error = FT_Load_Glyph(_face,FT_Get_Char_Index(_face,character),FT_LOAD_DEFAULT); 
    if(_error)
    {
        throw std::runtime_error("Text Component: Failed to load text component");
    }

    _error = FT_Get_Glyph(_face->glyph,&_glyph);
    if(_error)
    {
        throw std::runtime_error("Text Component: Failed to create bitmap from glyph");
    }
    

    _error = FT_Glyph_To_Bitmap(&_glyph,ft_render_mode_normal,0,true);
    if(_error)
    {
        throw std::runtime_error("Text Component: Failed to create bitmap from glyph");
    }

    _bitmapGlyph = (FT_BitmapGlyph)_glyph;
    FT_Bitmap& bitmap = _bitmapGlyph->bitmap;

    int width   = neares_pow_2(bitmap.width);
    int height  = neares_pow_2(bitmap.rows);

    {
        //Scoped
        _expanded_bitmapdata = std::shared_ptr<GLubyte>(new GLubyte[2* width * height],
            [](GLubyte * data)
            {
                delete [] data;
            }
        );

        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                _expanded_bitmapdata.get()[2 * (i + j * width)] 
                = _expanded_bitmapdata.get()[2 * (i + j * width) + 1] =
                    (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width * j];
            }
        }
    }

}