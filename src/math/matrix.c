#include "math/matrix.h"

void matrix_4x4f_multiply(struct matrix_4x4f_t *a, struct matrix_4x4f_t *b) {
  struct matrix_4x4f_t result = {0};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        result.m[i][j] += a->m[i][k] * b->m[k][j];
      }
    }
  }

  *a = result;
}

void matrix_4x4f_identity(struct matrix_4x4f_t *matrix) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j)
        matrix->m[i][j] = 1;
      else
        matrix->m[i][j] = 0;
    }
  }
}

void matrix_4x4d_multiply(struct matrix_4x4d_t *a, struct matrix_4x4d_t *b) {
  struct matrix_4x4d_t result = {0};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        result.m[i][j] += a->m[i][k] * b->m[k][j];
      }
    }
  }

  *a = result;
}

void matrix_4x4d_identity(struct matrix_4x4d_t *matrix) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j)
        matrix->m[i][j] = 1;
      else
        matrix->m[i][j] = 0;
    }
  }
}
