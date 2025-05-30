#include "projection.h"
#include "math/matrix.h"

#include <string.h>

void projection_perspective(Matrix_4x4f *matrix, float left, float right, float bottom, float top, float near, float far) {
  float m[4][4] = {
    { 2 * near / (right - left), 0, (right + left) / (right - left), 0 },
    { 0, 2 * near / (top - bottom), (top + bottom) / (top - bottom), 0 },
    { 0, 0, -(far + near) / (far - near), -2 * far * near / (far - near) },
    { 0, 0, -1, 0 }
  };

  memcpy(&matrix->m, m, sizeof(float) * 4 * 4);
}

void projection_perspective_symmetrical(Matrix_4x4f *matrix, float width, float height, float near, float far) {
  float m[4][4] = {
    {(2 * near) / width, 0, 0, 0},
    {0, (2 * near) / height, 0, 0},
    { 0, 0, -(far + near) / (far - near), -2 * far * near / (far - near) },
    { 0, 0, -1, 0 }
  };

  memcpy(&matrix->m, m, sizeof(float) * 4 * 4);
}

// Too fuckin lazy
// Not anymore bithc
void projection_orthographic(Matrix_4x4f *matrix, float left, float right, float bottom, float top, float near, float far) {
  float m[4][4] = {
    {2 / (right - left), 0, 0, -(right + left) / (right - left)},
    {0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom)},
    {0, 0, -2 / (far - near), -(far + near) / (far - near)},
    {0, 0, 0, 1}
  };

  memcpy(&matrix->m, m, sizeof(float) * 4 * 4);
}

void projection_orthographic_symmetrical(Matrix_4x4f *matrix, float width, float height, float near, float far) {
  float m[4][4] = {
    {2 / width, 0, 0, 0},
    {0, 2 / height, 0, 0},
    {0, 0, -2 / (far - near), -(far + near) / (far - near)},
    {0, 0, 0, 1}
  };

  memcpy(&matrix->m, m, sizeof(float) * 4 * 4);
}
