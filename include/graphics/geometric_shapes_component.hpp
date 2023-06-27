#ifndef _BASIC_SHAPES_COMPONENT
#define _BASIC_SHAPES_COMPONENT

#include <memory>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <conversions/space_vector_units.hpp>
#include <graphics/shader_handler.hpp>
#include <graphics/window_component.hpp>

#define TESTING_VERTICES 1
template <class _ShapeType>
class Shape2DComponent : std::enable_shared_from_this<Shape2DComponent<_ShapeType>>
{
    public:
        Shape2DComponent(std::shared_ptr<GladGLContext> windowContext):
        _shaderHandler("./shaders/shapeVertex.vs","./shaders/shapeFrag.fs","",windowContext)
        {
            _windowContext = windowContext;
            _shaderHandler.generateShaderProgram();
            // Vertex Array Object
            _windowContext->GenVertexArrays(1,&VertexAttributeObject);
            _windowContext->BindVertexArray(VertexAttributeObject);

            // Vertex Buffer Object
            _windowContext->GenBuffers(1,&VertexBufferObject);
            _windowContext->BindVertexArray(VertexAttributeObject);

            
            _windowContext->GenBuffers(1, &ElementBufferObject);
            _windowContext->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
            _windowContext->BufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
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
        unsigned int ElementBufferObject;
        ShaderHandler _shaderHandler;
        std::shared_ptr<GladGLContext> _windowContext;
        #if TESTING_VERTICES == 1
        GLfloat vertices[20] = 
        {
            -0.1f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
            0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
            -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
        };
        GLuint elements[6] = 
        {
            0, 1, 2,
            2, 3, 0
        };
        #endif
};

class Rectangle: public Shape2DComponent<Rectangle>
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

class Line: public Shape2DComponent<Line>
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

class Triangle: public Shape2DComponent<Triangle>
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