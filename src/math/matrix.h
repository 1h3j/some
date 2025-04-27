#ifndef MATRIX_H
#define MATRIX_H

struct matrix_4x4d_t {
  double m[4][4];
};

struct matrix_4x4f_t {
  float m[4][4];
};

// Float
void matrix_4x4f_multiply(struct matrix_4x4f_t *a, struct matrix_4x4f_t *b);
void matrix_4x4f_identity(struct matrix_4x4f_t *matrix);

// Double
void matrix_4x4d_multiply(struct matrix_4x4d_t *a, struct matrix_4x4d_t *b);
void matrix_4x4d_identity(struct matrix_4x4d_t *matrix);

#endif // !MATRIX_H
