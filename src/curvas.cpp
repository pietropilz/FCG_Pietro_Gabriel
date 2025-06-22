#include "../include/curvas.h"
#include "../include/matrices.h"

#define RAIO 500.0
#define CENTRO_X 0.0
#define CENTRO_Z  0.0


const glm::vec4 P1 = {0.0f, 0.0f, 20.0f, 1.0f};
const glm::vec4 P2 = {0.0f, 10.0f, 0.0f, 1.0f};
const glm::vec4 P3 = {0.0f, 0.0f, 0.0f, 1.0f};
const glm::vec4 P4 = {20.0f, 0.0f, 20.0f, 1.0f};

glm::vec4 bezier(float t);
glm::vec4 bezier_circulo_cima(float t);
glm::vec4 bezier_circulo_baixo(float t);



const glm::vec4 circulo[] ={
    glm::vec4(CENTRO_X-RAIO, 0.0f, CENTRO_Z, 1.0f),
    glm::vec4(CENTRO_X-RAIO/1.4142f, 0.0f, CENTRO_Z - RAIO, 1.0f),
    glm::vec4(CENTRO_X+RAIO/1.4142f, 0.0f, CENTRO_Z - RAIO, 1.0f),
    glm::vec4(CENTRO_X+RAIO, 0.0f, CENTRO_Z, 1.0f),

    glm::vec4(CENTRO_X+RAIO, 0.0f, CENTRO_Z, 1.0f),
    glm::vec4(CENTRO_X+RAIO/1.4142f, 0.0f, CENTRO_Z + RAIO, 1.0f),
    glm::vec4(CENTRO_X-RAIO/1.4142f, 0.0f, CENTRO_Z + RAIO, 1.0f),
    glm::vec4(CENTRO_X-RAIO, 0.0f, CENTRO_Z, 1.0f),
};

void curva_mov(float delta_t, glm::vec4& bezier_pos){
    float t = std::fmod(delta_t, 2.0f) / 2.0f;

    bezier_pos = bezier(t);
}

void curva_circulo(float delta_t, glm::vec4& bezier_pos, float& angulo){
    float t = std::fmod(delta_t, 4.0f) / 2.0f;

    if(t < 1.0f) bezier_pos = bezier_circulo_cima(t);
    else bezier_pos = bezier_circulo_baixo(t - 1.0f);

    glm::vec4 auxiliar = bezier_pos - glm::vec4(0.0f,0.0f,0.0f,1.0f);
    auxiliar /= norm(auxiliar);
    float valor_cos = acos(dotproduct(auxiliar, glm::vec4(0.0f,0.0f,-1.0f, 0.0f)));
    angulo = (bezier_pos[0] >= 0) ? valor_cos : -valor_cos;
}

glm::vec4 bezier_circulo_baixo(float t){
    glm::vec4 ponto12 = circulo[4] + t*(circulo[5] - circulo[4]);
    glm::vec4 ponto23 = circulo[5] + t*(circulo[6] - circulo[5]);
    glm::vec4 ponto34 = circulo[6] + t*(circulo[7] - circulo[6]);

    glm::vec4 ponto123 = ponto12 + t*(ponto23 - ponto12);
    glm::vec4 ponto234 = ponto23 + t*(ponto34 - ponto23);

    return ponto123 + t*(ponto234 - ponto123);
}

glm::vec4 bezier_circulo_cima(float t){
    glm::vec4 ponto12 = circulo[0] + t*(circulo[1] - circulo[0]);
    glm::vec4 ponto23 = circulo[1] + t*(circulo[2] - circulo[1]);
    glm::vec4 ponto34 = circulo[2] + t*(circulo[3] - circulo[2]);

    glm::vec4 ponto123 = ponto12 + t*(ponto23 - ponto12);
    glm::vec4 ponto234 = ponto23 + t*(ponto34 - ponto23);

    return ponto123 + t*(ponto234 - ponto123);
}

glm::vec4 bezier(float t) {
    glm::vec4 ponto12 = P1 + t*(P2 - P1);
    glm::vec4 ponto23 = P2 + t*(P3 - P2);
    glm::vec4 ponto34 = P3 + t*(P4 - P3);

    glm::vec4 ponto123 = ponto12 + t*(ponto23 - ponto12);
    glm::vec4 ponto234 = ponto23 + t*(ponto34 - ponto23);

    return ponto123 + t*(ponto234 - ponto123);
}
