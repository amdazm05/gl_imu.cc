#include "graphics/window_component.hpp"

WindowRenderComponent::WindowRenderComponent()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //Adding a custom deleter resolves assertions and makes this safer 
    _Window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(480, 480, "Window", NULL, NULL)
        ,[](GLFWwindow*window)
        {
            glfwDestroyWindow(window);
        }
    );
    _WindowContext = std::make_shared<GladGLContext>(new GladGLContext);
    glfwMakeContextCurrent(_Window.get());
    _WindowContext->Viewport(0, 0, 480, 480);
}

WindowRenderComponent::~WindowRenderComponent()
{
    glfwTerminate();
}

void WindowRenderComponent::renderWindow()
{
    glfwMakeContextCurrent(_Window.get());

    _WindowContext->ClearColor(0.5, 0.5, 0.5, 1.0f);
    _WindowContext->Clear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(_Window.get());
}

inline std::shared_ptr<WindowRenderComponent> WindowRenderComponent::getInstance()
{
    return shared_from_this();
}

inline std::shared_ptr<GLFWwindow> WindowRenderComponent::getWindowInstance()
{
    return _Window;
}

inline std::shared_ptr<GladGLContext> WindowRenderComponent::getWindowContextInstance()
{
    return _WindowContext;
}

void WindowRenderComponent::add_callbacks(std::function<void(
            GLFWwindow* window, 
            int key, 
            int scancode, 
            int action, 
            int mods)> callback)
{
    _keyCallback = callback;
}

//Some helpful resource
//https://stackoverflow.com/questions/25496801/why-is-this-shared-ptr-throwing-an-assert-when-it-goes-out-of-scope