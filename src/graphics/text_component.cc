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

void TextComponent::init()
{
    setTextFontProperties(20,"./assets/SFBold.ttf");
    renderGlyph();
    generateBitMapImage();

    glGenTextures(1, &tex_handle);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, _bitmap.buffer);
    
}

 void TextComponent::renderText(std::string && inputText,std::pair<double,double> renderPosition,std::tuple<uint8_t,uint8_t,uint8_t> color)
 {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int win_width, win_height;
    glfwGetFramebufferSize(_windowContext.get(), &win_width, &win_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, win_width, 0, win_height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
     // Render whatever you want
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glBegin(GL_QUADS);
        glTexCoord2d(0,1); glVertex2i((win_width - tex_width) / 2, (win_height - tex_height) / 2);
        glTexCoord2d(1,1); glVertex2i((win_width + tex_width) / 2, (win_height - tex_height) / 2);
        glTexCoord2d(1,0); glVertex2i((win_width + tex_width) / 2, (win_height + tex_height) / 2);
        glTexCoord2d(0,0); glVertex2i((win_width - tex_width) / 2, (win_height + tex_height) / 2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glfwSwapBuffers(_windowContext.get());
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
        std::cout<<"font \n";
    }
    _errorhandle = FT_Set_Char_Size(_face, 0, (int)(fontSize * 1), 30, 30);
    if(_errorhandle)
    {
        std::cout<<"char size font \n";
    }
}
