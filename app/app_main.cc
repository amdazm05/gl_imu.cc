#include <iostream>
#include "graphics/window_component.hpp"
#include "graphics/cursors_component.hpp"
#include "graphics/text_component.hpp"

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
        std::cout<<"Closing"<<std::endl;
    }
}
void cursor_enter_callback(GLFWwindow* window, int entered)
{
    if (entered)
    {
        std::cout<<"Entered .."<<std::endl;
    }
    else
    {
        // The cursor left the content area of the window
    }
}

int main()
{
    glfwInit();
    WindowRenderComponent Window;
    CursorsOptionsComponent Cursor(Window.getWindowInstance());
    TextComponent text(Window.getWindowInstance());
    Cursor.setEnterExitCallbacks(cursor_enter_callback);
    Window.add_keyboard_callback(key_callback);
    std::cout<<(uint64_t)(Window.getWindowInstance().get())<<std::endl;

    while (Window.isWindowComponentClosed())
    {
        glfwPollEvents();
        Window.renderWindow();
        text.renderText("asd",{0,0},{255,255,255});
    }

    return 0;
}
