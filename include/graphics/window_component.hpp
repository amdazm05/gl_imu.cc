#ifndef _WINDOWCOMP
#define _WINDOWCOMP

#include <memory>
#include <functional>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class WindowRenderComponent : std::enable_shared_from_this<WindowRenderComponent>
{
    public:
        WindowRenderComponent();
        ~WindowRenderComponent();
        std::shared_ptr<WindowRenderComponent> getInstance();
        std::shared_ptr<GLFWwindow> getWindowInstance();
        std::shared_ptr<GladGLContext> getWindowContextInstance();
        bool isWindowComponentClosed();
        void renderWindow();
        void add_callbacks(std::function<void(
            GLFWwindow* window, 
            int key, 
            int scancode, 
            int action, 
            int mods)> callback);
    private:
        std::function<void(
            GLFWwindow* window, 
            int key, 
            int scancode, 
            int action, 
            int mods)> _keyCallback;
        std::shared_ptr<GLFWwindow> _Window;
        std::shared_ptr<GladGLContext> _WindowContext;
};

#endif //_WINDOWCOMP