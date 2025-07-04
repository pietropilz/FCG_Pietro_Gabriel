#ifndef _ESTEGO_H
#define _ESTEGO_H



#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <GLFW/glfw3.h>

#include "matrices.h"
#include "curvas.h"

#define PI 3.1415926

struct Estego
{
    glm::vec4 central;
    glm::vec4 posicao;
    float angulo;
    glm::vec4 bbox_min;
    glm::vec4 bbox_max;
    float tempo_salvo;

    Estego() :
        central(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
        posicao(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)),
        angulo(0.0f),
        bbox_min(glm::vec4(0.0f)),
        bbox_max(glm::vec4(0.0f)),
        tempo_salvo(0.0f)
    {}

     glm::mat4 ModelMatrix() const {
        return Matrix_Translate(posicao.x, posicao.y, posicao.z)
                * Matrix_Rotate_Y(-angulo + PI);
    }

    void bezier(float tempo){
        if((tempo - tempo_salvo) > 4.0f ) tempo_salvo = tempo;
        float delta = tempo - tempo_salvo;

        angulo = (2.0f*PI)*delta / 4.0f;

        curva_circulo(delta/2.0f, posicao, angulo);
        posicao += central;
    }


    void novaPos(glm::vec4& pos){
        central = pos;
        angulo = 0.0f;
        tempo_salvo = 0.0f;
    }

};

#endif


