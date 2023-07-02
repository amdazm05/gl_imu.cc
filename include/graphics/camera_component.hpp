#ifndef _CAMERA_COMPONENT
#define _CAMERA_COMPONENT

#include <memory>
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class CameraComponent : std::enable_shared_from_this<CameraComponent>
{
    public:
        CameraComponent();
        ~CameraComponent();
        void setAngle(/*Add Space Coordinates here*/);
        void setRotation(/*Add space coordinate based rotation here*/);
        // Getters to be placed here
        void updateViewTransform();
    private:
        glm::mat4 _viewTransform;
        glm::mat4 _worldTransform
        glm::vec3 _speed;
        glm::vec3 _position;
};

#endif //_CAMERA_COMPONENT