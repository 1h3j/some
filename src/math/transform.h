#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "angles.h"
#include "matrix.h"
#include "vectors.h"

typedef struct matrix_4x4f_t transform_fl_t;
typedef struct matrix_4x4d_t transform_do_t;

// float
void transform_fl_translate(transform_fl_t *transform, struct vec3f_t offset);

void transform_fl_scale_sc(transform_fl_t *transform, float scalar);

void transform_fl_scale_ve(transform_fl_t *transform, struct vec3f_t scale);

void transform_fl_shear_x(transform_fl_t *transform, struct vec3f_t v);

void transform_fl_shear_y(transform_fl_t *transform, struct vec3f_t v);

void transform_fl_shear_z(transform_fl_t *transform, struct vec3f_t v);

void transform_fl_rotate_x(transform_fl_t *transform, radians_angle_t angle);

void transform_fl_rotate_y(transform_fl_t *transform, radians_angle_t angle);

void transform_fl_rotate_z(transform_fl_t *transform, radians_angle_t angle);

void transform_fl_vec3f(transform_fl_t *transform, struct vec3f_t *v);

// double
void transform_do_translate(transform_do_t *transform, struct vec3d_t offset);

void transform_do_scale_sc(transform_do_t *transform, double scalar);

void transform_do_scale_ve(transform_do_t *transform, struct vec3d_t scale);

void transform_do_shear_x(transform_do_t *transform, struct vec3d_t v);

void transform_do_shear_y(transform_do_t *transform, struct vec3d_t v);

void transform_do_shear_z(transform_do_t *transform, struct vec3d_t v);

void transform_do_rotate_x(transform_do_t *transform, radians_angle_t angle);

void transform_do_rotate_y(transform_do_t *transform, radians_angle_t angle);

void transform_do_rotate_z(transform_do_t *transform, radians_angle_t angle);

void transform_do_vec3d(transform_fl_t *transform, struct vec3d_t *v);

#endif // !TRANSFORM_H
