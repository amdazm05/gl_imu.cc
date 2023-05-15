#ifndef _CURSORS_COMPONENT
#define _CURSORS_COMPONENT

#include <glfw/glfw3.h>
#include <memory>
#include <iostream>
#include "util/functionutils.tpp"

class CursorsOptionsComponent: std::enable_shared_from_this<CursorsOptionsComponent>
{
    public:
        enum CursorOptions
        {
            DISABLE_CURSOR  =  GLFW_CURSOR_DISABLED  ,
            HIDDEN_CURSOR   =  GLFW_CURSOR_HIDDEN    ,
            NORMAL_CURSOR   =  GLFW_CURSOR_NORMAL    ,
        };

        /// @brief Use the standard cursor instance here
        /// @param windowContext 
        CursorsOptionsComponent(std::shared_ptr<GLFWwindow> windowContext);
        /// @brief Create a imaged based cursor here 
        /// @param windowContext 
        /// @param image 
        CursorsOptionsComponent(std::shared_ptr<GLFWwindow> windowContext,GLFWimage&& image);
        CursorsOptionsComponent() =delete;
        ~CursorsOptionsComponent();
        void createCursorWithImage();
        void setCursorMode(std::uint32_t CursorOptionsMode);
        void updateCursorPositionForceFully();
        void setWindowContext(std::shared_ptr<GLFWwindow> windowContext);
        void setEnterExitCallbacks(void(*enterExitCallback)(GLFWwindow* window, int entered));
        void setPositionCallbacks(void(*positionCallback)(GLFWwindow* window, double xpos, double ypos));
        
    private:
        /// @brief first is x , and second is y
        function_utils::function_ptr<void(*)(GLFWwindow* window, int entered)> enterExitCallback_experimental;
        function_utils::function_ptr<void(*)(GLFWwindow* window, double xpos, double ypos)> positionCallback;
        std::shared_ptr<GLFWwindow> _refWindowContext;
        std::shared_ptr<GLFWcursor> _cursorInstance;
        GLFWimage _image;
};

#endif //_CURSOURS_COMPONENT

//Interesting read
// https://stackoverflow.com/questions/43762651/how-does-stdtie-work