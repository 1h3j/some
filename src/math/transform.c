#include "transform.h"
#include "math/matrix.h"
#include <math.h>

// clang-format off
void transform_f_translate(transform_f_t *transform, struct vec3f_t offset) {
  struct matrix_4x4f_t matrix;
  matrix_4x4f_identity(&matrix);

  matrix.m[0][3] = offset.x;
  matrix.m[1][3] = offset.y;
  matrix.m[2][3] = offset.z;

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_scale_sc(transform_f_t *transform, float scalar) {
  struct matrix_4x4f_t matrix;
  matrix_4x4f_identity(&matrix);

  matrix.m[0][0] = scalar;
  matrix.m[1][1] = scalar;
  matrix.m[2][2] = scalar;

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_scale_ve(transform_f_t *transform, struct vec3f_t scale) {
  struct matrix_4x4f_t matrix;
  matrix_4x4f_identity(&matrix);

  matrix.m[0][0] = scale.x;
  matrix.m[1][1] = scale.y;
  matrix.m[2][2] = scale.z;

  matrix_4x4f_multiply(transform, &matrix);
}

// TODO : Finish Shearing
void transform_f_shear_x(transform_f_t *transform, struct vec3f_t v) {
  struct matrix_4x4f_t matrix = {{
    {1, 0, 0, 0},
    {v.y, 1, 0, 0},
    {v.z, 0, 1, 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_shear_y(transform_f_t *transform, struct vec3f_t v) {
  struct matrix_4x4f_t matrix = {{
    {1, v.x, 0, 0},
    {0, 1, 0, 0},
    {0, v.z, 1, 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_shear_z(transform_f_t *transform, struct vec3f_t v) {
  struct matrix_4x4f_t matrix = {{
    {1, 0, v.x, 0},
    {0, 1, v.y, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_rotate_x(transform_f_t *transform, radians_angle_t angle) {
  struct matrix_4x4f_t matrix = {{
    {1, 0, 0, 0},
    {0, cosf(angle), -sinf(angle), 0},
    {0, sinf(angle), cosf(angle), 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_rotate_y(transform_f_t *transform, radians_angle_t angle) {
  struct matrix_4x4f_t matrix = {{
    {cosf(angle), 0, sinf(angle), 0},
    {0, 1, 0, 0},
    {-sinf(angle), 0, cosf(angle), 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_rotate_z(transform_f_t *transform, radians_angle_t angle) {
  struct matrix_4x4f_t matrix = {{
    {cosf(angle), -sinf(angle), 0, 0},
    {sinf(angle), cosf(angle), 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_vec4f(transform_f_t *transform, struct vec4f_t *v) {
  for (int i=0; i<4; i++) {
    float a = ((float*)&v->x)[i];
    ((float*)&v->x)[i] = 0; // :troll:

    for (int j=0; j<4; j++) {
      ((float*)&v->x)[i] += transform->m[i][0] * a;
    }
  }
}

// DOubles

void transform_d_translate(transform_d_t *transform, struct vec3d_t offset) {
  struct matrix_4x4d_t matrix;
  matrix_4x4d_identity(&matrix);

  matrix.m[0][3] = offset.x;
  matrix.m[1][3] = offset.y;
  matrix.m[2][3] = offset.z;

  matrix_4x4d_multiply(transform, &matrix);
}

  struct matrix_4x4d_t matrix;
       void transform_d_scale_sc(transform_d_t *transform, double scalar) {
  matrix_4x4d_identity(&matrix);

  matrix.m[0][0] = scalar;
  matrix.m[1][1] = scalar;
  matrix.m[2][2] = scalar;

  matrix_4x4d_multiply(transform, &matrix);
}

void transform_d_scale_ve(transform_d_t *transform, struct vec3d_t scale) {
  struct matrix_4x4d_t matrix;
  matrix_4x4d_identity(&matrix);

  matrix.m[0][0] = scale.x;
  matrix.m[1][1] = scale.y;
  matrix.m[2][2] = scale.z;

  matrix_4x4d_multiply(transform, &matrix);
}

void transform_d_shear_x(transform_d_t *transform, struct vec3d_t v) {}

void transform_d_shear_y(transform_d_t *transform, struct vec3d_t v) {}

void transform_d_shear_z(transform_d_t *transform, struct vec3d_t v) {}

void transform_d_rotate_x(transform_d_t *transform, radians_angle_t angle) {
  struct matrix_4x4d_t matrix = {{
    {1, 0, 0, 0},
    {0, cos(angle), -sin(angle), 0},
    {0, sin(angle), cos(angle), 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4d_multiply(transform, &matrix);
}

void transform_d_rotate_y(transform_d_t *transform, radians_angle_t angle) {
  struct matrix_4x4d_t matrix = {{
    {cos(angle), 0, sin(angle), 0},
    {0, 1, 0, 0},
    {-sin(angle), 0, cos(angle), 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4d_multiply(transform, &matrix);
}

void transform_d_rotate_z(transform_d_t *transform, radians_angle_t angle) {
  struct matrix_4x4d_t matrix = {{
    {cos(angle), -sin(angle), 0, 0},
    {sin(angle), cos(angle), 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4d_multiply(transform, &matrix);
}
