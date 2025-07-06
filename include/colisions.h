#ifndef _COLISIONS_H
#define _COLISIONS_H

#include <vector>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <GLFW/glfw3.h>

#include "Arvores.h"
#include "dino.h"
#include "estego.h"
#include "matrices.h"


bool colisao_arvores(Arvores& arvores, const Dino& dino);

bool colisao_Dinos(const Dino& dino, const Estego& estego);

bool verifica_plano(const Dino& dino);

#endif



