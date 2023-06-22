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
