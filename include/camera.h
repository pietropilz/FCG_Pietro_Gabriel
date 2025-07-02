#ifndef _CAMERA_H
#define _CAMERA_H

#include <cmath>
#include "dino.h"
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <GLFW/glfw3.h>


void atualiza_lookCamera(glm::vec4& cam_position, glm::vec4& cam_vector, Dino);
void atualiza_freeCamera(glm::vec4& cam_position, const glm::vec4& cam_vector, const glm::vec4& obj_pos);
glm::mat4 projection_game(bool g_UsePerspectiveProjection, float g_ScreenRatio);
#endif

