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
    // generateBitMapImage();    
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

int next_power_2( int a )
{
	int rval=1;
	while(rval<a) rval<<=1;
	return rval;
}

void TextComponent::renderGlyph()
{
    FT_UInt glyph_index = FT_Get_Char_Index(_face, (FT_UInt32)('A'));
    if(FT_Load_Glyph(_face, glyph_index, FT_LOAD_DEFAULT))
    {
        std::cout<<"error loading glyph"<<std::endl;
    }
    if(FT_Get_Glyph(_face->glyph, &_glyph))
    {
        std::cout<<"error glyph load "<<std::endl;
    }
    FT_Glyph_To_Bitmap(&_glyph,ft_render_mode_normal,0,1);
    FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)_glyph;
    FT_Bitmap& bitmap=bitmap_glyph->bitmap;

    int width = next_power_2( bitmap.width );
	int height = next_power_2( bitmap.rows );

	//Allocate memory for the texture data.
	GLubyte* expanded_data = new GLubyte[ 2 * width * height];

	for(int j=0; j <height;j++) 
    {
		for(int i=0; i < width; i++)
        {
			expanded_data[2*(i+j*width)]= expanded_data[2*(i+j*width)+1] = 
				(i>=bitmap.width || j>=bitmap.rows) ?
				0 : bitmap.buffer[i + bitmap.width*j];
		}
    }

    glBindTexture( GL_TEXTURE_2D, tex_handle);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);


    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		  0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data );

    delete [] expanded_data;
    GLuint list_base=glGenLists(1);

	glNewList(list_base+'a',GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D,tex_handle);

	glTranslatef(bitmap_glyph->left,0,0);

	glPushMatrix();
	glTranslatef(0,bitmap_glyph->top-bitmap.rows,0);

	float	x=(float)bitmap.width / (float)width,
			y=(float)bitmap.rows / (float)height;

	glBegin(GL_QUADS);
	glTexCoord2d(0,0); glVertex2f(0,bitmap.rows);
	glTexCoord2d(0,y); glVertex2f(0,0);
	glTexCoord2d(x,y); glVertex2f(bitmap.width,0);
	glTexCoord2d(x,0); glVertex2f(bitmap.width,bitmap.rows);
	glEnd();
	glPopMatrix();
	glTranslatef(_face->glyph->advance.x >> 6 ,0,0);
	glEndList();
}

void TextComponent::setTextFontProperties(std::uint8_t fontSize,std::string && fontInformation)
{
    _errorhandle = FT_New_Face(_library, fontInformation.c_str(),0,&_face);
    if(_errorhandle)
    {
        std::cout<<"font \n";
    }
    // Freetype measures font size in terms of 1/64th of pixels.
    _errorhandle = FT_Set_Char_Size(_face, (fontSize<<6), (fontSize)<<6 , 30, 30);
    if(_errorhandle)
    {
        std::cout<<"char size font \n";
    }    
}
