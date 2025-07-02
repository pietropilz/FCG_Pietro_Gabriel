#include "../include/colisions.h"


#include <utility>
#include <iterator>

bool colisaoCilindroPonto(const Arvores& arvores, const Dino& dino, std::vector<int>& colisoes);

bool colisao_arvores(Arvores& arvores, const Dino& dino)
{
    std::vector<int> valores_possiveisX;
    float dino_X = dino.posicao.x;
    float limite_inferior_X = dino_X - 10.0f;
    float limite_superior_X = dino_X + 10.0f;

    auto it_inicio_X = std::lower_bound(arvores.valores_X.begin(), arvores.valores_X.end(), limite_inferior_X,
        [](const std::pair<float, int>& par, float valor) {return par.first < valor;});

    auto it_fim_X = std::upper_bound(arvores.valores_X.begin(), arvores.valores_X.end(), limite_superior_X,
        [](float valor, const std::pair<float, int>& par) {return valor < par.first;});

    for (auto it = it_inicio_X; it != it_fim_X; ++it)
    {
        valores_possiveisX.push_back(it->second);
    }

    std::vector<int> valores_possiveisZ;
    float dino_Z = dino.posicao.z;
    float limite_inferior_Z = dino_Z - 10.0f;
    float limite_superior_Z = dino_Z + 10.0f;

    auto it_inicio_Z = std::lower_bound(arvores.valores_Z.begin(), arvores.valores_Z.end(), limite_inferior_Z,
        [](const std::pair<float, int>& par, float valor) {return par.first < valor;});

    auto it_fim_Z = std::upper_bound(arvores.valores_Z.begin(), arvores.valores_Z.end(), limite_superior_Z,
        [](float valor, const std::pair<float, int>& par) {return valor < par.first;});

    for (auto it = it_inicio_Z; it != it_fim_Z; ++it)
    {
        valores_possiveisZ.push_back(it->second);
    }

    std::sort(valores_possiveisX.begin(), valores_possiveisX.end());
    std::sort(valores_possiveisZ.begin(), valores_possiveisZ.end());

    std::vector<int> ids_colisao;

    std::set_intersection(
        valores_possiveisX.begin(), valores_possiveisX.end(),
        valores_possiveisZ.begin(), valores_possiveisZ.end(),
        std::back_inserter(ids_colisao)
    );

    if(ids_colisao.empty()) return false;


    return colisaoCilindroPonto(arvores,dino, ids_colisao);
}


bool entre_retasperpendiculares(glm::vec4 reta1, glm::vec4 reta2, glm::vec4 ponto){

    float valor1 = reta1[0]*ponto[0] + reta1[2]*ponto[2];
    float valor2 = reta2[0]*ponto[0] + reta2[2]*ponto[2];

    return valor1 >= 0 && valor2 >= 0;
}

bool colisaoCilindroPonto(const Arvores& arvores, const Dino& dino, std::vector<int>& colisoes){
    glm::vec4 Cubomenor = dino.bbox_min;
    glm::vec4 Cubomaior = dino.bbox_max;
    glm::vec4 Cilindro = arvores.bbox_max;

    Cubomaior = dino.ModelMatrix()*Cubomaior;
    Cubomenor = dino.ModelMatrix()*Cubomenor;


    glm::vec4 ponto1 = Cubomenor;
    glm::vec4 ponto2 = glm::vec4(Cubomenor[0], Cubomenor[1], Cubomaior[2], 1.0f);
    glm::vec4 ponto3 = glm::vec4(Cubomaior[0], Cubomenor[1], Cubomenor[2], 1.0f);
    glm::vec4 ponto4 = Cubomaior;

    for(int i =0; i < colisoes.size(); i++){
        glm::vec4 ponto = arvores.pos[colisoes[i]];

        bool teste1 = entre_retasperpendiculares(ponto3 - ponto1, ponto2-ponto1, ponto - ponto1);
        bool teste2 = entre_retasperpendiculares(ponto3 - ponto4, ponto2-ponto4, ponto - ponto4);

        if(teste1 && teste2) return true;
    }
    return false;
}
