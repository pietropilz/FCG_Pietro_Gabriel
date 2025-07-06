#include "../include/moving.h"

#define MAX_SPEED   20.0
#define ACCELERATION    10.0
#define TURN 1.0

bool tecla_D = false;
bool tecla_S = false;
bool tecla_A = false;
bool tecla_W = false;

float speed = 0.0f;
float speedA = 0.0f;
float last_speed = 0.0f;
float last_speedA = 0.0f;

double g_LastCursorPosX, g_LastCursorPosY;
float g_Theta = 0, g_Phi =0;

bool g_LeftMouseButtonPressed = false;


void desloca(glm::vec4& obj_pos, glm::vec4& obj_vec, float& obj_angle, float delta_t)
{
    constexpr float max_speed = (float)MAX_SPEED;

    if (g_Theta != 0.0f)
    {
        float x_antigo = obj_vec[0];
        float z_antigo = obj_vec[2];

        float cos_theta = cos(g_Theta);
        float sin_theta = sin(g_Theta);

        obj_vec[0] = x_antigo * cos_theta - z_antigo * sin_theta;
        obj_vec[2] = x_antigo * sin_theta + z_antigo * cos_theta;

        obj_angle -= g_Theta;
        g_Theta = 0.0f;
    }


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

    if (!tecla_S && !tecla_W)
    {
        if(speed>0) speed -= speed * delta_t;
        else if(speed <0) speed -= speed  * delta_t;
    }



   if (tecla_A)
    {
        float acceleration = (float)(ACCELERATION/4.0f)*(1 - speedA/(max_speed/4.0f));
        speedA += acceleration*delta_t;
    }

    if (tecla_D)
    {
        float deaceleration = (float)(ACCELERATION/4.0f)*(1 + speedA/(max_speed/4.0f));
        speedA -= delta_t*deaceleration;
    }


    if (!tecla_A && !tecla_D)
    {
        if(speedA>0) speedA -= speedA * delta_t;
        else if(speedA <0) speedA -= speedA  * delta_t;
    }

    obj_pos += obj_vec*speed*delta_t;
    glm::vec4 transversal = crossproduct(obj_vec, glm::vec4(0.0f,1.0f,0.0f,0.0f));

    obj_pos -= transversal*speedA*delta_t;

    last_speedA = speedA;
    last_speed = speed;
    dino.velocidade = speed;
}

void avaliaColisao(glm::vec4& vetor, glm::vec4& pos, float angle, Dino& dino)
{
    dino.vetor = vetor;
    dino.posicao = pos;
    dino.angulo = angle;

    speed = 0.0f;
    speedA = 0.0f;
    last_speed = 0.0f;
    last_speedA = 0.0f;
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

/*
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_LeftMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        g_LeftMouseButtonPressed = false;
        g_CameraPhi = 0;
        g_CameraTheta = 0;
    }
}
*/

void inicializaCursor(GLFWwindow* window){
    glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
}

void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    float dx = xpos - g_LastCursorPosX;
    float dy = ypos - g_LastCursorPosY;

    g_Theta = 0.01f*dx;
    g_Phi   = 0.01f*dy;


    g_LastCursorPosX = xpos;
    g_LastCursorPosY = ypos;
}
