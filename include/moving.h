#ifndef _MOVING_H
#define _MOVING_H

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <GLFW/glfw3.h>
#include "carro.h"

extern Carro carro;
extern bool freeCamera;

void desloca(glm::vec4& obj_pos, glm::vec4& obj_vec, float& obj_angle, float delta_t);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod);

#endif
