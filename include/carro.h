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
    float pi = 3.1415926f;

    Carro()
    {
        posicao = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        vetor = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
        velocidade = 0.0f;
        angulo = 0.0f;
    }

     glm::mat4 ModelMatrix() const {
        return Matrix_Translate(posicao[0], posicao[1]-0.80f, posicao[2]) *
               Matrix_Rotate_Y(3*pi/2)*
               Matrix_Rotate_Y(angulo)*
               Matrix_Translate(0.0f,0.0f,3.0f)* //mudar o 3.0
               Matrix_Scale(0.01f, 0.01f, 0.01f);

    }


};


#endif // CARRO_H
