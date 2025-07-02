#ifndef _COLISIONS_H
#define _COLISIONS_H

#include <vector>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <GLFW/glfw3.h>

#include "Arvores.h"
#include "dino.h"
#include "matrices.h"


bool colisao_arvores(Arvores& arvores, const Dino& dino);



#endif



