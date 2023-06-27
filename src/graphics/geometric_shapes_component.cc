#include "graphics/geometric_shapes_component.hpp"


Rectangle::Rectangle(std::shared_ptr<GladGLContext> windowContext):
Shape2DComponent<Rectangle>(windowContext)
{
    

}

Rectangle::~Rectangle()
{

}

void Rectangle::render()
{

}
void Rectangle::setDimensions(std::tuple<float,float,float> & dim3)
{

}
void Rectangle::setPosition(SpaceUnits::Coordinates<float> & position3)
{

}

Line::Line(std::shared_ptr<GladGLContext> windowContext):
Shape2DComponent<Line>(windowContext)
{
    

}
Line::~Line()
{

}
void Line::setDimensions(std::tuple<float,float,float> & dim3)
{

}
void Line::setPosition(SpaceUnits::Coordinates<float> & position3)
{

}
void Line::render()
{
    _windowContext->Disable(GL_BLEND);
    _windowContext->Disable(GL_DEPTH_TEST); 
    _windowContext->Disable(GL_STENCIL_TEST);
    // etc...
    _shaderHandler.useProgram();
    _windowContext->BindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    _windowContext->BufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    GLint posAttrib = _windowContext->GetAttribLocation(_shaderHandler.getShaderId(), "position");
    // Remember that in some core profiles its mandatory to have VertexArray binded before
    _windowContext->BindVertexArray(VertexAttributeObject);
    _windowContext->EnableVertexAttribArray(posAttrib);
    _windowContext->VertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

    GLint colAttrib = _windowContext->GetAttribLocation(_shaderHandler.getShaderId(), "color_shape");
    _windowContext->EnableVertexAttribArray(colAttrib);
    _windowContext->VertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    // _windowContext->BindVertexArray(VertexAttributeObject);
    _windowContext->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
    _windowContext->DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


Triangle::Triangle(std::shared_ptr<GladGLContext> windowContext) :
Shape2DComponent<Triangle>(windowContext)
{

}
Triangle::~Triangle()
{

}
void Triangle::setDimensions(std::tuple<float,float,float> & dim3)
{

}
void Triangle::setPosition(std::tuple<float,float> & position3)
{

}
void Triangle::render()
{

}

// Error Handling issues Make a handler and make life easy
// err = (Window.getWindowContextInstance())->GetError();
// std::cout << "OpenGL Error Text: " << err << "\n"; 