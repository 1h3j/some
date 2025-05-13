#include "projection.h"

#include <string.h>

void projection_perspective(struct matrix_4x4f_t *matrix, float left, float right, float bottom, float top, float near, float far) {
  float m[4][4] = {
    {
      2 * near / (right - left),
      0,
      (right + left) / (right - left),
      0
    },
    {
      0,
      2 * near / (top - bottom),
      (top + bottom) / (top - bottom),
      0
    },
    {
      0,
      0,
      -(far + near) / (far - near),
      -2 * far * near / (far - near)
    },
    {
      0,
      0,
      -1,
      0
    }
  };

  memcpy(&matrix->m, m, sizeof(float) * 4 * 4);
}
