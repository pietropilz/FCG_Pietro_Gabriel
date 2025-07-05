#ifndef _MOVING_H
#define _MOVING_H

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <GLFW/glfw3.h>
#include "dino.h"

extern Dino dino;
extern bool freeCamera;

void desloca(glm::vec4& obj_pos, glm::vec4& obj_vec, float& obj_angle, float delta_t);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod);
//void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void inicializaCursor(GLFWwindow* window);
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);

void avaliaColisao(glm::vec4& vetor, glm::vec4& pos, float angle, Dino& dino);

#endif
