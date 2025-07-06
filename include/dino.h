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
    glm::vec4 mover;
    glm::vec4 tamanho;
    float velocidade;
    float angulo;
    glm::mat4 model;
    glm::vec4 bbox_min;
    glm::vec4 bbox_max;
    int comidos;

    Dino()
    {
        posicao = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        mover = glm::vec4(-0.4f, 0.0f, -1.4f, 0.0f);
        tamanho = glm::vec4(0.01f, 0.01f, 0.01f, 0.0f);
        vetor = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
        velocidade = 0.0f;
        angulo = 0.0f;
        comidos = 0;
    }

     glm::mat4 ModelMatrix() const {
        return Matrix_Translate(posicao[0], posicao[1]-0.8f, posicao[2]) *
               Matrix_Rotate_Y(angulo + 3.0f*pi/2.0f)*
               Matrix_Translate(mover[0], mover[1], mover[2])*
               Matrix_Scale(tamanho[0], tamanho[1], tamanho[2]);
    }


};


#endif // CARRO_H
