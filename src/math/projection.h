#ifndef PROJECTION_H
#define PROJECTION_H

#include "matrix.h"

/**
 * Calculated the perspective matrix from various parameters which define a frustum.
 *
 * @param matrix Pointer to a matrix.
 * @param left   The left point of the near plane. 
 * @param right  The right point of the near plane. 
 * @param top    The top point of the near plane. 
 * @param bottom The bottom point of the near plane. 
 * @param near   Distance of the near plane.
 * @param far    Distance of the far plane.
*/
void projection_perspective(struct matrix_4x4f_t *matrix, float left, float right, float bottom, float top, float near, float far);

/**
 * Calculated the orthographic matrix from various parameters which define a rectangle.
 *
 * @param matrix Pointer to a matrix.
 * @param left   The left plane.
 * @param right  The right plane.
 * @param top    The top plane.
 * @param bottom The bottom plane.
 * @param near   Distance of the near plane.
 * @param far    Distance of the far plane.
*/
void projection_orthographic(struct matrix_4x4f_t *matrix, float left, float right, float bottom, float top, float near, float far);

#endif // PROJECTION_H
