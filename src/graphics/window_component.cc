#include "graphics/window_component.hpp"
#include <iostream>
WindowRenderComponent::WindowRenderComponent()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //Adding a custom deleter resolves assertions and makes this safer 
    _Window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(480, 480, "Window23", NULL, NULL)
        ,[](GLFWwindow*window)
        {
            glfwDestroyWindow(window);
        }
    );
    glfwMakeContextCurrent(_Window.get());
    _WindowContext = std::make_shared<GladGLContext>(new GladGLContext[1]());
    gladLoadGLContext(_WindowContext.get(), glfwGetProcAddress);
    glfwMakeContextCurrent(_Window.get());
    _WindowContext->Viewport(0, 0, 480, 480);
}

WindowRenderComponent::~WindowRenderComponent()
{
    glfwTerminate();
}

bool WindowRenderComponent::isWindowComponentClosed()
{
    return !glfwWindowShouldClose(_Window.get());
}

void WindowRenderComponent::renderWindow()
{
    // _WindowContext->ClearColor(0, 0.9, 0, 1.0f);
    _WindowContext->Clear(GL_COLOR_BUFFER_BIT);
}

std::shared_ptr<WindowRenderComponent> WindowRenderComponent::getInstance()
{
    return shared_from_this();
}

std::shared_ptr<GLFWwindow> WindowRenderComponent::getWindowInstance()
{
    return _Window;
}

std::shared_ptr<GladGLContext> WindowRenderComponent::getWindowContextInstance()
{
    return _WindowContext;
}

void WindowRenderComponent::add_keyboard_callback(void(*callback)(
            GLFWwindow* window, 
            int key, 
            int scancode, 
            int action, 
            int mods))
{
    _keyCallback = callback;
    glfwSetKeyCallback(_Window.get(),_keyCallback.get());
}

//Some helpful resource
//https://stackoverflow.com/questions/25496801/why-is-this-shared-ptr-throwing-an-assert-when-it-goes-out-of-scope