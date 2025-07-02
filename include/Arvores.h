#ifndef _ARVORES_H
#define _ARVORES_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <GLFW/glfw3.h>

#include "matrices.h"

struct Arvores
{
    int n;
    std::vector<glm::vec4> pos;
    std::vector<bool> existe;
    std::vector<std::pair<float,int>> valores_X;
    std::vector<std::pair<float,int>> valores_Z;
    glm::vec4 bbox_min;
    glm::vec4 bbox_max;


    Arvores() : n(0)
    {
        for(float x = -200.0f; x <= 200.00f; x += 35.0f)
        {
            for(float z = -200.0f; z <= 200.00f; z += 35.0f)
            {
                pos.push_back(glm::vec4(x,0.0f,z,1.0f));
                valores_X.push_back(std::pair<float,int>(x,n));
                valores_Z.push_back(std::pair<float,int>(z,n));
                existe.push_back(true);
                n++;
            }
        }
        std::sort(valores_X.begin(), valores_X.end(), [](const std::pair<float,int>& a, const std::pair<float,int>& b) {
                    return a.first < b.first;});

        std::sort(valores_Z.begin(), valores_Z.end(), [](const std::pair<float,int>& a, const std::pair<float,int>& b) {
            return a.first < b.first;});
    }

    glm::mat4 ModelMatrix(int n) const {
        return Matrix_Translate(pos[n][0], 0.0f, pos[n][2]) * Matrix_Scale(0.4f, 0.4f, 0.4f);
    }
};

#endif

