#ifndef PROJECTION_H
#define PROJECTION_H

#include "matrix.h"

void projection_perspective(struct matrix_4x4f_t *matrix, float left, float right, float bottom, float top, float near, float far);

#endif // PROJECTION_H
