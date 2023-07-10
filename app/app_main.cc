#include <iostream>
#include "graphics/window_component.hpp"
#include "graphics/cursors_component.hpp"
#include "graphics/text_component.hpp"
#include "graphics/geometric_shapes_component.hpp"
#include "graphics/error_logger.hpp"
#include "stream/serialstreamer.hpp"

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
    SerialStreamer<WindowsSerialStreamer> SerialPort;
    SerialPort.init("\\\\.\\COM5");
    SerialPort.ReadAvailableData();
    glfwInit();
    WindowRenderComponent Window;
    CursorsOptionsComponent Cursor(Window.getWindowInstance());
    TextComponent text(Window.getWindowInstance(),Window.getWindowContextInstance());
    Shape2DComponent<Line> Shape(Window.getWindowContextInstance());
    GraphicsErrorHandler ErrorHandler("LogFile.log",Window.getWindowContextInstance());
    text.init("Antonio.ttf",12);
    Cursor.setEnterExitCallbacks(cursor_enter_callback);
    Window.add_keyboard_callback(key_callback);
    std::cout<<(uint64_t)(Window.getWindowInstance().get())<<std::endl;
    while (Window.isWindowComponentClosed())
    {
        Window.renderWindow();
        text.printtxt("Name:",{25.0f, 25.0f});
        text.printtxt("Ahmed",{25.0f + 120.f, 25.0f});
        text.printtxt("Azeem",{25.0f + 240.f, 25.0f});
        Shape.render();
        ErrorHandler.LogErrors();
        glfwSwapBuffers(Window.getWindowInstance().get());
        glfwPollEvents();
    }

    return 0;
}
