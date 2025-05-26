#ifndef MATRIX_H
#define MATRIX_H

struct matrix_4x4d_t {
  double m[4][4];
};

struct matrix_4x4f_t {
  float m[4][4];
};

// Float

/**
 * Combine two matrices through multiplication.
 *
 * @param a Right matrix. Also the matrix that this function will output to.
 * @param b The matrix that applies the transformations to the first matrix.
*/
void matrix_4x4f_multiply(struct matrix_4x4f_t *a, struct matrix_4x4f_t *b);

/**
 * Change a matrix to a matrix identity
 *
 * @param matrix Pointer to the matrix
*/
void matrix_4x4f_identity(struct matrix_4x4f_t *matrix);

// Double

/**
 * Combine two matrices through multiplication.
 *
 * @param a Right matrix. Also the matrix that this function will output to.
 * @param b The matrix that applies the transformations to the first matrix.
*/
void matrix_4x4d_multiply(struct matrix_4x4d_t *a, struct matrix_4x4d_t *b);

/**
 * Change a matrix to a matrix identity
 *
 * @param matrix Pointer to the matrix
*/
void matrix_4x4d_identity(struct matrix_4x4d_t *matrix);


#endif // !MATRIX_H
