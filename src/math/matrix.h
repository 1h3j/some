#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
  double m[4][4];
} Matrix_4x4d;

typedef struct {
  float m[4][4];
} Matrix_4x4f;

// Float

/**
 * Combine two matrices through multiplication.
 *
 * @param a Right matrix. Also the matrix that this function will output to.
 * @param b The matrix that applies the transformations to the first matrix.
*/
void matrix_4x4f_multiply(Matrix_4x4f *a, Matrix_4x4f *b);

/**
 * Change a matrix to a matrix identity
 *
 * @param matrix Pointer to the matrix
*/
void matrix_4x4f_identity(Matrix_4x4f *matrix);

// Double

/**
 * Combine two matrices through multiplication.
 *
 * @param a Right matrix. Also the matrix that this function will output to.
 * @param b The matrix that applies the transformations to the first matrix.
*/
void matrix_4x4d_multiply(Matrix_4x4d *a, Matrix_4x4d *b);

/**
 * Change a matrix to a matrix identity
 *
 * @param matrix Pointer to the matrix
*/
void matrix_4x4d_identity(Matrix_4x4d *matrix);


#endif // !MATRIX_H
