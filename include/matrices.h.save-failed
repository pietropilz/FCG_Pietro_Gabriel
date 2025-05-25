#ifndef _MATRICES_H
#define _MATRICES_H

#include <cstdio>
#include <cstdlib>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Matrix(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
glm::mat4 Matrix_Identity();
glm::mat4 Matrix_Translate(float dx, float dy, float dz);
glm::mat4 Matrix_Scale(float sx, float sy, float sz);
glm::mat4 Matrix_Rotate_X(float angle);
glm::mat4 Matrix_Rotate_Y(float angle);
glm::mat4 Matrix_Rotate_Z(float angle);
glm::mat4 Matrix_Rotate(float angle, glm::vec4 axis);
glm::mat4 Matrix_Camera_View(glm::vec4 position_c, glm::vec4 view_vector, glm::vec4 up_vector);
glm::mat4 Matrix_Orthographic(float left, float right, float bottom, float top, float near, float far);
glm::mat4 Matrix_Perspective(float fovy, float aspect, float near, float far);
glm::vec4 crossproduct(glm::vec4 u, glm::vec4 v);
float dotproduct(glm::vec4 u, glm::vec4 v);
float norm(glm::vec4 u);
void PrintMatrix(glm::mat4 M);
void PrintVector(glm::vec4 v);
void PrintMatrixVectorProduct(glm::mat4 M, glm::vec4 v);
void PrintMatrixVectorProductDivW(glm::mat4 M, glm::vec4 v);

#endif // _MATRICES_H
