#include "../include/colisions.h"

#include <algorithm>
#include <vector>
#include <iterator>

void colisao_arvores(Arvores& arvores, const Dino& dino)
{
    std::vector<int> valores_possiveisX;
    float dino_X = dino.posicao.x;
    float limite_inferior_X = dino_X - 10.0f;
    float limite_superior_X = dino_X + 10.0f;

    auto it_inicio_X = arvores.valores_X.lower_bound(limite_inferior_X);
    auto it_fim_X = arvores.valores_X.upper_bound(limite_superior_X);

    for (auto it = it_inicio_X; it != it_fim_X; ++it)
    {
        valores_possiveisX.push_back(it->second);
    }

    std::vector<int> valores_possiveisZ;
    float dino_Z = dino.posicao.z;
    float limite_inferior_Z = dino_Z - 10.0f;
    float limite_superior_Z = dino_Z + 10.0f;

    auto it_inicio_Z = arvores.valores_Z.lower_bound(limite_inferior_Z);
    auto it_fim_Z = arvores.valores_Z.upper_bound(limite_superior_Z);

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

    for (int num : ids_colisao)
    {
        arvores.existe[num] = false;
    }
}
