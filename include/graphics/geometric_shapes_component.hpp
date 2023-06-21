#ifndef _BASIC_SHAPES_COMPONENT
#define _BASIC_SHAPES_COMPONENT

#include <memory>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <conversions/space_vector_units.hpp>
template <class _ShapeType>
class Shape2DComponent
{
    public:
        Shape2DComponent(SpaceUnits::Coordinates<float> && _positionCoordiates);
        ~Shape2DComponent();
        void render();
        void setDimensions(std::tuple<float,float,float> dim3);
        void setPosition(std::tuple<float,float> position3);
        // To basically use features from other windows
        std::shared_ptr<_ShapeType> getInstance();
    private:
        std::shared_ptr<_ShapeType> _childClass;
};

class Rectangle: Shape2DComponent<Rectangle>
{
    public:
        Rectangle();
        ~Rectangle();
        void render();
        void setDimensions(std::tuple<float,float,float> dim3);
        void setPosition(SpaceUnits::Coordinates<float> position3);
    protected:
        std::array<SpaceUnits::Coordinates<float>,4> _vertices;
};

class Line: Shape2DComponent<Line>
{
    public:
        Line();
        ~Line();
        void setDimensions(std::tuple<float,float,float> dim3);
        void setPosition(std::tuple<float,float> position3);
        void render();
    protected:
        // Start and stop point
        std::array<SpaceUnits::Coordinates<float>,2>  _vertices;
};

class Triangle: Shape2DComponent<Triangle>
{
    public:
        Triangle();
        ~Triangle();
        void setDimensions(std::tuple<float,float,float> dim3);
        void setPosition(std::tuple<float,float> position3);
        void render();
    protected:
        std::array<SpaceUnits::Coordinates<float>,3>  _vertices;
};

#endif //_BASIC_SHAPES_COMPONENT