#ifndef _BASIC_SHAPES_COMPONENT
#define _BASIC_SHAPES_COMPONENT

#include <memory>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <conversions/space_vector_units.hpp>
#include <graphics/shader_handler.hpp>
#include <graphics/window_component.hpp>
template <class _ShapeType>
class Shape2DComponent : std::enable_shared_from_this<Shape2DComponent<_ShapeType>>
{
    public:
        Shape2DComponent(std::shared_ptr<GladGLContext> windowContext):
        shaderHandler("./shaders/shapeFragmentShader.fs","./shaders/shapeVertexShader.fs","",windowContext)
        {
            _windowContext = windowContext;
        }
        ~Shape2DComponent()
        {
            // Do nothing for now
        }
        void render()
        {
            static_cast<_ShapeType*>(this)->render();
        }
        void setDimensions(std::tuple<float,float,float> & dim3)
        {
            static_cast<_ShapeType*>(this)->setDimensions(dim3);
        }
        void setPosition(SpaceUnits::Coordinates<float> & position3)
        {
            static_cast<_ShapeType*>(this)->setPosition(position3);
        }
        // To basically use features from other windows
        std::shared_ptr<Shape2DComponent<_ShapeType>> getInstance()
        {
            return std::enable_shared_from_this<Shape2DComponent<_ShapeType>>::shared_from_this();
        }
    protected:
        SpaceUnits::Coordinates<float> _position;
        unsigned int VertexBufferObject;
        unsigned int VertexAttributeObject;
        ShaderHandler shaderHandler;
        std::shared_ptr<GladGLContext> _windowContext;
};

class Rectangle: Shape2DComponent<Rectangle>
{
    public:
        Rectangle(std::shared_ptr<GladGLContext> windowContext);
        ~Rectangle();
        void render();
        void setDimensions(std::tuple<float,float,float> & dim3);
        void setPosition(SpaceUnits::Coordinates<float> & position3);
    protected:
        std::array<SpaceUnits::Coordinates<float>,4> _vertices;
};

class Line: Shape2DComponent<Line>
{
    public:
        Line(std::shared_ptr<GladGLContext> windowContext);
        ~Line();
        void setDimensions(std::tuple<float,float,float> & dim3);
        void setPosition(SpaceUnits::Coordinates<float> & position3);
        void render();
    protected:
        // Start and stop point
        std::array<SpaceUnits::Coordinates<float>,2>  _vertices;
};

class Triangle: Shape2DComponent<Triangle>
{
    public:
        Triangle(std::shared_ptr<GladGLContext> windowContext);
        ~Triangle();
        void setDimensions(std::tuple<float,float,float> & dim3);
        void setPosition(std::tuple<float,float> & position3);
        void render();
    protected:
        std::array<SpaceUnits::Coordinates<float>,3>  _vertices;
};

#endif //_BASIC_SHAPES_COMPONENT