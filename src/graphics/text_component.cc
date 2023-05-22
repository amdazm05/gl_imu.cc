#include "graphics/text_component.hpp"

TextComponent::TextComponent(std::shared_ptr<GLFWwindow> windowInstance)
{
    _windowContext = windowInstance;
    _errorhandle =  FT_Init_FreeType(&_library);
    if(_errorhandle)
    {

    }
}
TextComponent::~TextComponent()
{

}

void TextComponent::generateBitMapImage()
{
    _bitmap = _face->glyph->bitmap;
}

void TextComponent::renderGlyph()
{
    FT_UInt glyph_index = FT_Get_Char_Index(_face, (FT_UInt32)('A'));
    FT_Load_Glyph(_face, glyph_index, FT_LOAD_DEFAULT);
    FT_Render_Glyph(_face->glyph, FT_RENDER_MODE_NORMAL);
}

void TextComponent::setTextFontProperties(std::uint8_t fontSize,std::string && fontInformation)
{
    _errorhandle = FT_New_Face(_library, fontInformation.c_str(),0,&_face);
    if(_errorhandle)
    {

    }
    _errorhandle = FT_Set_Char_Size(_face, 0, (int)(fontSize * 64), 300, 300);
    if(_errorhandle)
    {

    }
}
