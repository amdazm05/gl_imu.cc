#include "graphics/text_component.hpp"

TextComponent::TextComponent(std::shared_ptr<GLFWwindow> windowInstance, std::shared_ptr<GladGLContext> windowContext)
: _shaderHandler("./shaders/textFrag.fs","./shaders/textVertex.vs","",windowContext)
{
    _window = windowInstance;
    _windowContext = windowContext;
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

    _shaderHandler.generateShaderProgram();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), 0.0f, static_cast<float>(600));
    _shaderHandler.useProgram();
    _windowContext->UniformMatrix4fv(_windowContext->GetUniformLocation(_shaderHandler.getShaderId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
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
        _windowContext->PixelStorei(GL_UNPACK_ALIGNMENT,1);
        for(unsigned char c =0 ;c< CHAR_MAX_COUNT;c++)
            make_display_lists(c);

        _windowContext->BindTexture(GL_TEXTURE_2D, 0);
    }
    // destroy FreeType once we're finished
    FT_Done_Face(_face);
    FT_Done_FreeType(_library);

    // configure VAO/VBO for texture quads
    // -----------------------------------
    _windowContext->GenVertexArrays(1, &_VAO);
    _windowContext->GenBuffers(1, &_VBO);
    _windowContext->BindVertexArray(_VAO);
    _windowContext->BindBuffer(GL_ARRAY_BUFFER, _VBO);
    _windowContext->BufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    _windowContext->EnableVertexAttribArray(0);
    _windowContext->VertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    _windowContext->BindBuffer(GL_ARRAY_BUFFER, 0);
    _windowContext->BindVertexArray(0);
    
}

void TextComponent::make_display_lists(char c)
{
    _error = FT_Load_Char(_face,c,FT_LOAD_RENDER); 
    if(_error)
    {
        throw std::runtime_error("Text Component: Failed to load text component");
    }

    unsigned int texture;
    _windowContext->GenTextures(1, &texture);
    _windowContext->BindTexture(GL_TEXTURE_2D, texture);
    _windowContext->TexImage2D(
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

    _windowContext->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    _windowContext->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    _windowContext->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    _windowContext->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Character character = {
                texture,
                glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
                glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
                static_cast<unsigned int>(_face->glyph->advance.x)
            };
    // Why copy if you can move
    _charactermap.insert(std::pair<char, Character>(c, std::move(character)));
}

void TextComponent::printtxt(std::string && text ,std::pair<float,float> position)  
{
    _windowContext->Enable(GL_BLEND);
    _windowContext->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _windowContext->Disable(GL_DEPTH_TEST);
    _shaderHandler.useProgram();
    _windowContext->Uniform3f(_windowContext->GetUniformLocation(_shaderHandler.getShaderId(), "textColor"), 0.5, 0.8f, 0.2f);
    _windowContext->ActiveTexture(GL_TEXTURE0);
    _windowContext->BindVertexArray(_VAO);
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) 
    {
        Character ch = _charactermap[*c];

        float xpos = position.first + ch.Bearing.x * 1.0f;
        float ypos = position.second - (ch.Size.y - ch.Bearing.y) * 1.0f;

        float w = ch.Size.x * 1.0f;
        float h = ch.Size.y * 1.0f;
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };

        _windowContext->BindTexture(GL_TEXTURE_2D, ch.TextureID);
        _windowContext->BindBuffer(GL_ARRAY_BUFFER, _VBO);
        _windowContext->BufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        _windowContext->BindBuffer(GL_ARRAY_BUFFER, 0);
        _windowContext->DrawArrays(GL_TRIANGLES, 0, 6);
        position.first += (ch.Advance >> 6) * 1.0f; 
    }
    _windowContext->BindVertexArray(0);
    _windowContext->BindTexture(GL_TEXTURE_2D, 0);
    _windowContext->Enable(GL_DEPTH_TEST);

}

