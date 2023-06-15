#ifndef _BASIC_SHAPES_COMPONENT
#define _BASIC_SHAPES_COMPONENT

#include <memory>


template <class _ShapeType>
class ShapeComponent
{
    public:
        ShapeComponent(std::pair<float, float> && _positionCoordiates);
        ~ShapeComponent();
        void render();

        // To basically use features from other windows
        std::shared_ptr<_ShapeType> getInstance();
    private:
        std::shared_ptr<_ShapeType> _childClass;
        std::pair<float,float> _Coordinates;
};

class Rectangle: ShapeComponent<Rectangle>
{
    public:
        Rectangle();
        ~Rectangle();
    protected:
        std::pair<float,float> _dimensions;
       
};

class Line: ShapeComponent<Line>
{
    public:
        Line();
        ~Line();
    protected:
        float _dimensions;
       
};

class Triangle: ShapeComponent<Triangle>
{
    public:
        Triangle();
        ~Triangle();
    protected:
        std::tuple<float,float,float>  _vertices;
       
};

#endif //_BASIC_SHAPES_COMPONENT