#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#include <vector>
#include "EditorManager.h"


const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 1.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


//window size
int W = 700;
int H = 700;


class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    //window size
    int Width;
    int Height;


    
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

 

    void SetWandH(int w, int h) {
        Width = w;
        Height = h;
    }
   

    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

  

    void ProcessMove(MOVE direction)
    {
        if (direction == FORWARD)
            Position += Front * MovementSpeed;
        if (direction == BACKWARD)
            Position -= Front * MovementSpeed;
        if (direction == LEFT)
            Position -= Right * MovementSpeed;
        if (direction == RIGHT)
            Position += Right * MovementSpeed;
    }

    void ProcessRotate(MOVE direction) {
        if (direction == RotateLY) {
            Yaw -= 5.0f;
        }
        if (direction == RotateRY) {
            Yaw += 5.0f;
        }
        updateCameraVectors();
    }


private:
    

    void updateCameraVectors()
    {
        //recalcul directia de observare
        Front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front.y = sin(glm::radians(Pitch));
        Front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(Front);


        //  recalculare vectorul Up si Right
        Right = glm::normalize(glm::cross(Front, WorldUp)); 
        Up = glm::normalize(glm::cross(Right, Front));
    }
};
#endif
