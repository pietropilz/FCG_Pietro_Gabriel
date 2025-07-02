#ifndef _ARVORES_H
#define _ARVORES_H

#include <cmath>
#include <vector>
#include <map>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <GLFW/glfw3.h>

struct Arvores
{
    int n;
    std::vector<glm::vec4> pos;
    std::vector<bool> existe;
    std::multimap<float,int> valores_X;
    std::multimap<float,int> valores_Z;


    Arvores() : n(0)
    {
        for(float x = -200.0f; x <= 200.00f; x += 35.0f)
        {
            for(float z = -200.0f; z <= 200.00f; z += 35.0f)
            {
                pos.push_back(glm::vec4(x,0.0f,z,1.0f));
                valores_X.insert({x,n});
                valores_Z.insert({z,n});
                existe.push_back(true);
                n++;
            }
        }
    }
};





void inicializaArvores(std::vector<glm::vec4>& arvoresPos, std::map<float,int>& ordenaX, std::map<float,int>& ordenaZ);


#endif

