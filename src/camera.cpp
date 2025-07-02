#include "../include/camera.h"
#include "../include/matrices.h"
#include "dino.h"

//Definições de distância da câmera para o objeto e altura da câmera em relação ao solo
#define DISTANCIA 10.0f
#define ALTURA 5.0f

#define NEARPLANE 0.1f
#define FARPLANE 200.0f

void atualiza_lookCamera(glm::vec4& cam_position, glm::vec4& cam_vector, Dino dino)
{
    constexpr const float distancia_total = std::sqrt(DISTANCIA*DISTANCIA + ALTURA*ALTURA);
    constexpr float inicial_Y = std::acos(ALTURA/distancia_total);

    glm::vec4 vetor = crossproduct(dino.vetor, glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));

    glm::vec4 obj_pos = dino.posicao - vetor*0.5f;


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
