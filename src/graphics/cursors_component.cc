#include "graphics/cursors_component.hpp"

CursorsOptionsComponent::CursorsOptionsComponent(std::shared_ptr<GLFWwindow> windowContext)
{
    _cursorInstance= std::shared_ptr<GLFWcursor>( glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR)
        ,[](GLFWcursor * cursor){glfwDestroyCursor(cursor);}
    );
    _refWindowContext  = windowContext;
    glfwSetCursor(windowContext.get(), _cursorInstance.get());
}
CursorsOptionsComponent::CursorsOptionsComponent(std::shared_ptr<GLFWwindow> windowContext,GLFWimage&& image)
{

}
CursorsOptionsComponent::~CursorsOptionsComponent()
{

}
void CursorsOptionsComponent::createCursorWithImage()
{

}
void CursorsOptionsComponent::setCursorMode(std::uint32_t CursorOptionsMode)
{

}
void CursorsOptionsComponent::updateCursorPositionForceFully()
{

}
void CursorsOptionsComponent::setWindowContext(std::shared_ptr<GLFWwindow> windowContext)
{

}

void CursorsOptionsComponent::setEnterExitCallbacks(void(*enterExitFunc)(GLFWwindow* window, int entered))
{
    this->enterExitCallback_experimental = enterExitFunc;
    glfwSetCursorEnterCallback(_refWindowContext.get(),enterExitCallback_experimental.get());
}