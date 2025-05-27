#ifndef PROJECTION_H
#define PROJECTION_H

#include "matrix.h"

/**
 * Calculate the perspective matrix from various parameters which define a frustum.
 *
 * @param matrix Pointer to a matrix.
 * @param left   The left point of the near plane. 
 * @param right  The right point of the near plane. 
 * @param top    The top point of the near plane. 
 * @param bottom The bottom point of the near plane. 
 * @param near   Distance of the near plane.
 * @param far    Distance of the far plane.
*/
void projection_perspective(Matrix_4x4f *matrix, float left, float right, float bottom, float top, float near, float far);

/**
 * Calculate the orthographic matrix from various parameters which define a rectangular prism.
 *
 * @param matrix Pointer to a matrix.
 * @param left   The left plane.
 * @param right  The right plane.
 * @param top    The top plane.
 * @param bottom The bottom plane.
 * @param near   Distance of the near plane.
 * @param far    Distance of the far plane.
*/
void projection_orthographic(Matrix_4x4f matrix, float left, float right, float bottom, float top, float near, float far);

#endif // PROJECTION_H
