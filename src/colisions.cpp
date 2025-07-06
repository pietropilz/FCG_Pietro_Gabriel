#include "../include/colisions.h"


#include <utility>
#include <iterator>

struct Bbox{
    glm::vec4 min;
    glm::vec4 max;
};

Bbox calculaBox(const glm::vec4& local_min, const glm::vec4& local_max, const glm::mat4& modelMatrix);
bool colisaoCubos(const glm::vec4& aM, const glm::vec4& am, const glm::vec4& bM, const glm::vec4& bm);
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

bool colisaoCilindroPonto(const Arvores& arvores, const Dino& dino, std::vector<int>& colisoes){
    glm::vec4 Cubomenor = dino.bbox_min;
    glm::vec4 Cubomaior = dino.bbox_max;

    Bbox correta = calculaBox(Cubomenor, Cubomaior, dino.ModelMatrix());
    Cubomaior = correta.max;
    Cubomenor = correta.min;

    float minX = Cubomenor.x;
    float maxX = Cubomaior.x;
    float minZ = Cubomenor.z;
    float maxZ = Cubomaior.z;

    for(int i = 0; i < static_cast<int>(colisoes.size()); i++) {
        glm::vec4 pos_arvore = arvores.pos[colisoes[i]];

        float cx = pos_arvore.x;
        float cz = pos_arvore.z;

        float raio = 0.05f;

        float px = std::max(minX, std::min(cx, maxX));
        float pz = std::max(minZ, std::min(cz, maxZ));

        float dx = cx - px;
        float dz = cz - pz;
        float dist2 = dx*dx + dz*dz;

        if(dist2 <= raio * raio) return true;
    }

    return false;
}


//--------------------------------------------------------------------------------------------------------------
Bbox calculaBox(const glm::vec4& local_min, const glm::vec4& local_max, const glm::mat4& modelMatrix)
{
        glm::vec4 cantos[8] = {
        glm::vec4(local_min.x, local_min.y, local_min.z, 1.0f),
        glm::vec4(local_max.x, local_min.y, local_min.z, 1.0f),
        glm::vec4(local_max.x, local_max.y, local_min.z, 1.0f),
        glm::vec4(local_min.x, local_max.y, local_min.z, 1.0f),
        glm::vec4(local_min.x, local_min.y, local_max.z, 1.0f),
        glm::vec4(local_max.x, local_min.y, local_max.z, 1.0f),
        glm::vec4(local_max.x, local_max.y, local_max.z, 1.0f),
        glm::vec4(local_min.x, local_max.y, local_max.z, 1.0f)
    };

    glm::vec4 boxInicial = modelMatrix * cantos[0];
    Bbox boxFinal = {boxInicial, boxInicial};


    for (int i = 1; i < 8; ++i) {
        glm::vec4 cantoTransformado = modelMatrix * cantos[i];

        boxFinal.min = glm::min(boxFinal.min, cantoTransformado);
        boxFinal.max = glm::max(boxFinal.max, cantoTransformado);
    }

    return boxFinal;
}

bool colisaoCubos(const glm::vec4& aM, const glm::vec4& am, const glm::vec4& bM, const glm::vec4& bm) {
    return (aM.x >= bm.x && am.x <= bM.x) &&
           (aM.y >= bm.y && am.y <= bM.y) &&
           (aM.z >= bm.z && am.z <= bM.z);
}

bool colisao_Dinos(const Dino& dino, const Estego& estego)
{
    Bbox dinoBox = calculaBox(dino.bbox_min, dino.bbox_max, dino.ModelMatrix());

    Bbox estegoBox = calculaBox(estego.bbox_min, estego.bbox_max, estego.ModelMatrix());

    return colisaoCubos(dinoBox.max, dinoBox.min, estegoBox.max, estegoBox.min);
}





bool verifica_plano(const Dino& dino)
{
    Bbox bdino = calculaBox(dino.bbox_min, dino.bbox_max, dino.ModelMatrix());

    return (bdino.max.x > 210.0f) || (bdino.max.z > 210) || (bdino.min.x < -210.0f) || (bdino.min.z < -210.0f);
}
