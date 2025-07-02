#ifndef DINO_H
#define DINO_H

#include <glm/glm.hpp>
#include <matrices.h>

const float pi = 3.1415926f;
class Dino
{
public:
    glm::vec4 posicao;
    glm::vec4 vetor;
    float velocidade;
    float angulo;
    glm::mat4 model;
    glm::vec4 bbox_min;
    glm::vec4 bbox_max;

    Dino()
    {
        posicao = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        vetor = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
        velocidade = 0.0f;
        angulo = 0.0f;
    }

     glm::mat4 ModelMatrix() const {
        return Matrix_Translate(posicao[0], posicao[1]-0.80f, posicao[2]) *
               Matrix_Rotate_Y(angulo + 3.0f*pi/2.0f)*
               Matrix_Translate(-1.0f,0.0f,-1.45f)*
               Matrix_Scale(0.01f, 0.01f, 0.01f);
    }


};


#endif // CARRO_H
