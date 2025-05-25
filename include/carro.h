#ifndef CARRO_H
#define CARRO_H

#include <glm/glm.hpp>
#include <matrices.h>

class Carro
{
public:
    glm::vec4 posicao;
    glm::vec4 vetor;
    float velocidade;
    float angulo;
    glm::mat4 model;

    Carro()
    {
        posicao = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        vetor = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
        velocidade = 0.0f;
        angulo = 0.0f;
    }

     glm::mat4 ModelMatrix() const {
        return Matrix_Translate(posicao[0], posicao[1] + 1.0f, posicao[2]) *
               Matrix_Scale(1.0f, 1.0f, 1.0f) *
               Matrix_Rotate_Y(angulo);
    }


};


#endif // CARRO_H
