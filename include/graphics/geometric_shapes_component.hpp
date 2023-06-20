#ifndef _BASIC_SHAPES_COMPONENT
#define _BASIC_SHAPES_COMPONENT

#include <memory>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
template <class _ShapeType>
class Shape2DComponent
{
    public:
        Shape2DComponent(std::pair<float, float> && _positionCoordiates);
        ~Shape2DComponent();
        void render();
        void setDimensions(std::tuple<float,float,float> dim3);
        void setPosition(std::tuple<float,float> position3);
        // To basically use features from other windows
        std::shared_ptr<_ShapeType> getInstance();
    private:
        std::shared_ptr<_ShapeType> _childClass;
        std::pair<float,float> _Coordinates;
};

class Rectangle: Shape2DComponent<Rectangle>
{
    public:
        Rectangle();
        ~Rectangle();
        void render();
        void setDimensions(std::tuple<float,float,float> dim3);
        void setPosition(std::tuple<float,float> position3);
    protected:
        std::pair<float,float> _dimensions;
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
        std::pair<float,float> _dimensions;
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
        std::tuple<float,float,float>  _vertices;
};

#endif //_BASIC_SHAPES_COMPONENT