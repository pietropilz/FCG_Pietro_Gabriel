#include "../include/moving.h"

#define MAX_SPEED   90.0
#define ACCELERATION    20.0
#define TURN 1.0



bool tecla_D = false;
bool tecla_S = false;
bool tecla_A = false;
bool tecla_W = false;

float speed = 0.0f;
float last_speed = 0.0f;

void desloca(glm::vec4& obj_pos, glm::vec4& obj_vec, float& obj_angle, float delta_t)
{
    constexpr float max_speed = (float)MAX_SPEED;


    if (tecla_W)
    {
        float acceleration = (float)ACCELERATION*(1- speed/max_speed);
        speed += acceleration*delta_t;
    }

    if (tecla_S)
    {
        if(speed > 0) speed -= (ACCELERATION*1.5f)*delta_t;

        float deaceleration = (ACCELERATION/4.0f)*(1 + speed/(max_speed/4.0f));
        speed -= delta_t*deaceleration;
    }

    if(speed*last_speed < 0)
    {
        speed = 0.0f;
        tecla_W = false, tecla_S = false;
    }

    if (!tecla_S && !tecla_W)
    {
        if(speed>0) speed -= speed * 0.1f * delta_t;
        else if(speed <0) speed -= speed * 0.1f * delta_t;
    }

    if(tecla_A || tecla_D)
    {
        constexpr float turn_rate = TURN/max_speed;

        float turn;

        if(fabs(speed) < 2.0f) turn = delta_t*fabs(speed)/2.0f;
        else turn = delta_t*(1/(1 + turn_rate*fabs(speed)));

        float dir = (speed >= 0.0f) ? 1.0f : -1.0f;

        if (tecla_A) obj_angle += dir * turn;
        if (tecla_D) obj_angle -= dir * turn;

        obj_vec = glm::vec4(-sin(obj_angle), 0.0f, -cos(obj_angle), 0.0f);
    }
    obj_pos += obj_vec*speed*delta_t;
    last_speed = speed;
    carro.velocidade = speed;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod)
{
    for (int i = 0; i < 10; ++i)
        if (key == GLFW_KEY_0 + i && action == GLFW_PRESS && mod == GLFW_MOD_SHIFT)
            std::exit(100 + i);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key == GLFW_KEY_D)
    {
        if (action == GLFW_PRESS) tecla_D = true;
        else if (action == GLFW_RELEASE) tecla_D = false;
    }
    if (key == GLFW_KEY_S)
    {
        if (action == GLFW_PRESS) tecla_S = true;
        else if (action == GLFW_RELEASE) tecla_S = false;
    }
    if (key == GLFW_KEY_A)
    {
        if (action == GLFW_PRESS) tecla_A = true;
        else if (action == GLFW_RELEASE) tecla_A = false;
    }
    if (key == GLFW_KEY_W)
    {
        if (action == GLFW_PRESS) tecla_W = true;
        else if (action == GLFW_RELEASE) tecla_W = false;
    }
    if(key == GLFW_KEY_C)
    {
        if(action == GLFW_PRESS) freeCamera = !freeCamera;
    }
}
