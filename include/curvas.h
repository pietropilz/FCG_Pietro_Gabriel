#ifndef _CURVAS_H
#define _CURVAS_H

#include <glm/glm.hpp>
#include <cmath>

void curva_mov(float delta_t, glm::vec4& bezier_pos);
void curva_circulo(float delta_t, glm::vec4& bezier_pos);

#endif
