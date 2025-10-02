#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "angles.h"
#include "matrix.h"
#include "vectors.h"

typedef Matrix_4x4f TransformF;
typedef Matrix_4x4d TransformD;

// -- float -- //

/**
 * Translates the transformation matrix by an offset.
 *
 * @param transform Pointer to a transformation matrix
 * @param offset   The offset to the transformation
 */
void transform_f_translate(TransformF *transform, Vec3f offset);

/**
 * Scales the transformation matrix uniformly by a scalar.
 *
 * @param transform Pointer to a transformation matrix
 * @param scalar    The uniform scale factor
 */
void transform_f_scale_sc(TransformF *transform, float scalar);

/**
 * Scales the transformation matrix by individual axis scale factors.
 *
 * @param transform Pointer to a transformation matrix
 * @param scale     The scale Vector
 */
void transform_f_scale_ve(TransformF *transform, Vec3f scale);

/**
 * Applies an X-axis shear to the transformation matrix.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Shear factors
 */
void transform_f_shear_x(TransformF *transform, Vec3f v);

/** Applies a Y-axis shear to the transformation matrix.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Shear factors
 */
void transform_f_shear_y(TransformF *transform, Vec3f v);

/**
 * Applies a Z-axis shear to the transformation matrix.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Shear factors
 */
void transform_f_shear_z(TransformF *transform, Vec3f v);

/**
 * Rotates the transformation matrix around the X axis.
 *
 * @param transform Pointer to a transformation matrix
 * @param angle     Rotation angle in radians
 */
void transform_f_rotate_x(TransformF *transform, AngleRad angle);

/**
 * Rotates the transformation matrix around the Y axis.
 *
 * @param transform Pointer to a transformation matrix
 * @param angle     Rotation angle in radians
 */
void transform_f_rotate_y(TransformF *transform, AngleRad angle);

/**
 * Rotates the transformation matrix around the Z axis.
 *
 * @param transform Pointer to a transformation matrix
 * @param angle     Rotation angle in radians
 */
void transform_f_rotate_z(TransformF *transform, AngleRad angle);

/**
 * Applies the transformation to a 3D float Vector.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Pointer to the Vector to transform (in-place)
 */
void transform_f_Vec3(TransformF *transform, Vec3f *v);


// -- double -- //

/**
 * Translates the transformation matrix by an offset.
 *
 * @param transform Pointer to a transformation matrix
 * @param offset    The offset to the transformation
 */
void transform_d_translate(TransformD *transform, Vec3d offset);

/**
 * Scales the transformation matrix uniformly by a scalar.
 *
 * @param transform Pointer to a transformation matrix
 * @param scalar    The uniform scale factor
 */
void transform_d_scale_sc(TransformD *transform, double scalar);

/**
 * Scales the transformation matrix by individual axis scale factors.
 *
 * @param transform Pointer to a transformation matrix
 * @param scale     The scale Vector
 */
void transform_d_scale_ve(TransformD *transform, Vec3d scale);

/**
 * Applies an X-axis shear to the transformation matrix.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Shear factors
 */
void transform_d_shear_x(TransformD *transform, Vec3d v);

/**
 * Applies a Y-axis shear to the transformation matrix.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Shear factors
 */
void transform_d_shear_y(TransformD *transform, Vec3d v);

/**
 * Applies a Z-axis shear to the transformation matrix.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Shear factors
 */
void transform_d_shear_z(TransformD *transform, Vec3d v);

/**
 * Rotates the transformation matrix around the X axis.
 *
 * @param transform Pointer to a transformation matrix
 * @param angle     Rotation angle in radians
 */
void transform_d_rotate_x(TransformD *transform, AngleRad angle);

/**
 * Rotates the transformation matrix around the Y axis.
 *
 * @param transform Pointer to a transformation matrix
 * @param angle     Rotation angle in radians
 */
void transform_d_rotate_y(TransformD *transform, AngleRad angle);

/**
 * Rotates the transformation matrix around the Z axis.
 *
 * @param transform Pointer to a transformation matrix
 * @param angle     Rotation angle in radians
 */
void transform_d_rotate_z(TransformD *transform, AngleRad angle);

/**
 * Applies the transformation to a 3D double Vector.
 *
 * @param transform Pointer to a transformation matrix
 * @param v         Pointer to the Vector to transform (in-place)
 */
void transform_d_vec3(TransformF *transform, Vec3d *v);

#endif // !TRANSFORM_H
