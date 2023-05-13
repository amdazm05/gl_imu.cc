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
        WindowRenderComponent(int width,int height)
        ~WindowRenderComponent();
        std::shared_ptr<WindowRenderComponent> getInstance();
        std::shared_ptr<GLFWwindow> getWindowInstance();
        std::shared_ptr<GladGLContext> getWindowContextInstance();
        bool isWindowComponentClosed();
        void renderWindow();
        void add_keyboard_callback(std::function<void(
            GLFWwindow* window, 
            int key, 
            int scancode, 
            int action, 
            int mods)> callback);
        void add_mouseposition_callback(std::function<void(
            GLFWwindow* window, 
            double xpos, 
            double ypos
        )>);
    private:
        std::function<void(
            GLFWwindow* window, 
            int key, 
            int scancode, 
            int action, 
            int mods)> _keyCallback;
        std::function<void(
            GLFWwindow* window, 
            double xpos, 
            double ypos
        )> _mousepositionCallback;
        std::shared_ptr<GLFWwindow> _Window;
        std::shared_ptr<GladGLContext> _WindowContext;
};

#endif //_WINDOWCOMP

// Continue reading this resource
// https://www.glfw.org/docs/3.3/input_guide.html#input_mouse