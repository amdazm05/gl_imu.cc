#include <iostream>
#include "graphics/window_component.hpp"

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
int main()
{
    glfwInit();
    WindowRenderComponent Window;
    Window.add_callbacks(key_callback);
    std::cout<<(uint64_t)(Window.getWindowInstance().get())<<std::endl;

    while (Window.isWindowComponentClosed())
    {
        glfwPollEvents();
        Window.renderWindow();
    }

    return 0;
}
