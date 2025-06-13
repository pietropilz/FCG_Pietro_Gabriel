#include "../include/camera.h"
#include "../include/matrices.h"
#include "carro.h"

//Definições de distância da câmera para o objeto e altura da câmera em relação ao solo
#define DISTANCIA 10.0f
#define ALTURA 5.0f

#define NEARPLANE 0.1f
#define FARPLANE 200.0f

double g_LastCursorPosX, g_LastCursorPosY;
float g_CameraTheta = 0, g_CameraPhi =0;

bool g_LeftMouseButtonPressed = false;

float angleY_antigo = 0;

void atualiza_lookCamera(glm::vec4& cam_position, glm::vec4& cam_vector, Carro carro)
{
    constexpr const float distancia_total = std::sqrt(DISTANCIA*DISTANCIA + ALTURA*ALTURA);
    constexpr float inicial_Y = std::acos(ALTURA/distancia_total);

    glm::vec4 vetor = crossproduct(carro.vetor, glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));

    glm::vec4 obj_pos = carro.posicao - vetor*1.5f;

    if(g_LeftMouseButtonPressed){
        float angleY = inicial_Y + g_CameraPhi;

        float angleX = (cam_vector[0] > 0) ? acos(-1.0f*cam_vector[2]) : -acos(-1.0f*cam_vector[2]);
        angleX += g_CameraTheta;

        constexpr float r = distancia_total;
        float y = r*cos(angleY);

        if(y < 0.1f) {angleY = angleY_antigo; y = r*cos(angleY);}

        float z = r*sin(angleY)*cos(angleX) + obj_pos[2];
        float x = -r*sin(angleY)*sin(angleX) + obj_pos[0];
        cam_position = glm::vec4(x,y,z, 1.0f);
        glm::vec4 look_at = obj_pos - cam_position;
        cam_vector = look_at/norm(look_at);

        angleY_antigo = angleY;
        return;
    }

    cam_position = obj_pos - cam_vector * DISTANCIA + glm::vec4(0.0f, ALTURA, 0.0f, 0.0f);
    glm::vec4 aux = obj_pos - cam_position;
    cam_vector = aux/norm(aux);
}

void atualiza_freeCamera(glm::vec4& cam_position, const glm::vec4& cam_vector, const glm::vec4& obj_pos){
    cam_position = obj_pos + cam_vector;
    cam_position.y += 1.0f;
}



glm::mat4 projection_game(bool g_UsePerspectiveProjection, float g_ScreenRatio)
{
    constexpr float nearplane = -NEARPLANE;  // Posição do "near plane"
    constexpr float farplane  = -FARPLANE; // Posição do "far plane"

    constexpr float g_CameraDistance = 2.5f;

    if (g_UsePerspectiveProjection)
    {
        float field_of_view = 3.141592 / 3.0f;
        return Matrix_Perspective(field_of_view, g_ScreenRatio, nearplane, farplane);
    }

    else
    {
        float t = 1.5f*g_CameraDistance/2.5f;
        float b = -t;
        float r = t*g_ScreenRatio;
        float l = -r;
        return Matrix_Orthographic(l, r, b, t, nearplane, farplane);
    }
}

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

void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{

    if (!g_LeftMouseButtonPressed)
        return;

    float dx = xpos - g_LastCursorPosX;
    float dy = ypos - g_LastCursorPosY;

    g_CameraTheta += 0.01f*dx;
    g_CameraPhi   += 0.01f*dy;


    g_LastCursorPosX = xpos;
    g_LastCursorPosY = ypos;
}
