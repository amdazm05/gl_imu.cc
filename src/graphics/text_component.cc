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
    _textheight = textheight;
    FT_Set_Char_Size(_face, _textheight<<6, _textheight<<6, 96,96);

    // List base is the count of contiguous "empty" lists allocated by GL
    _listbase = glGenLists(CHAR_MAX_COUNT);

    // glGenTextures generates the unique names provided by GL taht are stored in textures
    if(_textures != nullptr)
        glGenTextures(CHAR_MAX_COUNT,_textures.get());

    for(uint8_t i=0;i<CHAR_MAX_COUNT;i++)
        make_display_lists((char)i,_face);

    FT_Done_Face(_face);
	//Ditto for the library.
	FT_Done_FreeType(_library);
}

void TextComponent::make_display_lists(char character, FT_Face faceCpy)
{
    _error = FT_Load_Glyph(faceCpy,FT_Get_Char_Index(faceCpy,character),FT_LOAD_DEFAULT); 
    if(_error)
    {
        throw std::runtime_error("Text Component: Failed to load text component");
    }

    _error = FT_Get_Glyph(faceCpy->glyph,&_glyph);
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

        glBindTexture( GL_TEXTURE_2D, _textures.get()[character]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height,
            0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, _expanded_bitmapdata.get());
    }

    glNewList(_listbase+character,GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D,_textures.get()[character]);
	glTranslatef(_bitmapGlyph->left,0,0);

	glPushMatrix();
	glTranslatef(0,_bitmapGlyph->top-bitmap.rows,0);

	float	x=(float)bitmap.width / (float)width,
			y=(float)bitmap.rows / (float)height;


	glBegin(GL_QUADS);
	glTexCoord2d(0,0); glVertex2f(0,bitmap.rows);
	glTexCoord2d(0,y); glVertex2f(0,0);
	glTexCoord2d(x,y); glVertex2f(bitmap.width,0);
	glTexCoord2d(x,0); glVertex2f(bitmap.width,bitmap.rows);
	glEnd();
	glPopMatrix();
	glTranslatef(faceCpy->glyph->advance.x >> 6 ,0,0);

	glEndList();

}

void pushScreenCoordinateMatrix() {
	glPushAttrib(GL_TRANSFORM_BIT);
	GLint	viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(viewport[0],viewport[2],viewport[1],viewport[3]);
	glPopAttrib();
}
void popProjectionMatrix() {
	glPushAttrib(GL_TRANSFORM_BIT);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
}

void TextComponent::printtxt(std::string && text ,std::pair<float,float> position)  
{
	float heightAdjusted =  _height/.63f;
    glColor3ub(0,0,0xff);
    glPushMatrix();
	glLoadIdentity();
	glScalef(1,.8+.3,1);
	glTranslatef(-120,0,0);
	pushScreenCoordinateMatrix();						
	GLuint font= _listbase;

	glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT  | GL_ENABLE_BIT | GL_TRANSFORM_BIT);	
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	glListBase(font);

	float modelview_matrix[16];	
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);	

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(position.first,position.second,0);
    glMultMatrixf(modelview_matrix);
    glCallLists(text.length(), GL_UNSIGNED_BYTE, text.c_str());
    glPopMatrix();
    glPopAttrib();

	popProjectionMatrix();
    glPopMatrix();
}

