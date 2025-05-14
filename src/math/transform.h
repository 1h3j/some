#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "angles.h"
#include "matrix.h"
#include "vectors.h"

typedef struct matrix_4x4f_t transform_fl_t;
typedef struct matrix_4x4d_t transform_do_t;

// -- float -- //

/**
 * Translates the transformation matrix by an offset.
 *
 * @param transform Pointer to a transformation matrix
 * @param offset   The offset to the transformation
 */
void transform_fl_translate(transform_fl_t *transform, struct vec3f_t offset);

/**
 * Scales the transformation matrix uniformly by a scalar.
 *
 * @param transform Pointer to a transformation matrix
 * @param scalar    The uniform scale factor
 */
void transform_fl_scale_sc(transform_fl_t *transform, float scalar);

/**
 * Scales the transformation matrix by individual axis scale factors.
 *
 * @param transform Pointer to a transformation matrix
 * @param scale     The scale vector
 */
void transform_fl_scale_ve(transform_fl_t *transform, struct vec3f_t scale);

/**
 * Applies an X-axis shear to the transformation matrix.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Shear factors
 */
void transform_fl_shear_x(transform_fl_t *transform, struct vec3f_t v);

/**
 * Applies a Y-axis shear to the transformation matrix.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Shear factors
 */
void transform_fl_shear_y(transform_fl_t *transform, struct vec3f_t v);

/**
 * Applies a Z-axis shear to the transformation matrix.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Shear factors
 */
void transform_fl_shear_z(transform_fl_t *transform, struct vec3f_t v);

/**
 * Rotates the transformation matrix around the X axis.
 *
 * @param transform Pointer to a transformation matrix
 * @param angle     Rotation angle in radians
 */
void transform_fl_rotate_x(transform_fl_t *transform, radians_angle_t angle);

/**
 * Rotates the transformation matrix around the Y axis.
 *
 * @param transform Pointer to a transformation matrix
 * @param angle     Rotation angle in radians
 */
void transform_fl_rotate_y(transform_fl_t *transform, radians_angle_t angle);

/**
 * Rotates the transformation matrix around the Z axis.
 *
 * @param transform Pointer to a transformation matrix
 * @param angle     Rotation angle in radians
 */
void transform_fl_rotate_z(transform_fl_t *transform, radians_angle_t angle);

/**
 * Applies the transformation to a 3D float vector.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Pointer to the vector to transform (in-place)
 */
void transform_fl_vec3f(transform_fl_t *transform, struct vec3f_t *v);


// -- double -- //

/**
 * Translates the transformation matrix by an offset.
 *
 * @param transform Pointer to a transformation matrix
 * @param offset    The offset to the transformation
 */
void transform_do_translate(transform_do_t *transform, struct vec3d_t offset);

/**
 * Scales the transformation matrix uniformly by a scalar.
 *
 * @param transform Pointer to a transformation matrix
 * @param scalar    The uniform scale factor
 */
void transform_do_scale_sc(transform_do_t *transform, double scalar);

/**
 * Scales the transformation matrix by individual axis scale factors.
 *
 * @param transform Pointer to a transformation matrix
 * @param scale     The scale vector
 */
void transform_do_scale_ve(transform_do_t *transform, struct vec3d_t scale);

/**
 * Applies an X-axis shear to the transformation matrix.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Shear factors
 */
void transform_do_shear_x(transform_do_t *transform, struct vec3d_t v);

/**
 * Applies a Y-axis shear to the transformation matrix.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Shear factors
 */
void transform_do_shear_y(transform_do_t *transform, struct vec3d_t v);

/**
 * Applies a Z-axis shear to the transformation matrix.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Shear factors
 */
void transform_do_shear_z(transform_do_t *transform, struct vec3d_t v);

/**
 * Rotates the transformation matrix around the X axis.
 *
 * @param transform Pointer to a transformation matrix
 * @param angle     Rotation angle in radians
 */
void transform_do_rotate_x(transform_do_t *transform, radians_angle_t angle);

/**
 * Rotates the transformation matrix around the Y axis.
 *
 * @param transform Pointer to a transformation matrix
 * @param angle     Rotation angle in radians
 */
void transform_do_rotate_y(transform_do_t *transform, radians_angle_t angle);

/**
 * Rotates the transformation matrix around the Z axis.
 *
 * @param transform Pointer to a transformation matrix
 * @param angle     Rotation angle in radians
 */
void transform_do_rotate_z(transform_do_t *transform, radians_angle_t angle);

/**
 * Applies the transformation to a 3D double vector.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Pointer to the vector to transform (in-place)
 */
void transform_do_vec3d(transform_fl_t *transform, struct vec3d_t *v);

#endif // !TRANSFORM_H
