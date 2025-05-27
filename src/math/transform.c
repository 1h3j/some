#include "transform.h"
#include "matrix.h"

#include <math.h>

// clang-format off
void transform_f_translate(TransformF *transform, Vec3f offset) {
  Matrix_4x4f matrix;
  matrix_4x4f_identity(&matrix);

  matrix.m[0][3] = offset.x;
  matrix.m[1][3] = offset.y;
  matrix.m[2][3] = offset.z;

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_scale_sc(TransformF *transform, float scalar) {
  Matrix_4x4f matrix;
  matrix_4x4f_identity(&matrix);

  matrix.m[0][0] = scalar;
  matrix.m[1][1] = scalar;
  matrix.m[2][2] = scalar;

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_scale_ve(TransformF *transform, Vec3f scale) {
  Matrix_4x4f matrix;
  matrix_4x4f_identity(&matrix);

  matrix.m[0][0] = scale.x;
  matrix.m[1][1] = scale.y;
  matrix.m[2][2] = scale.z;

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_shear_x(TransformF *transform, Vec3f v) {
  Matrix_4x4f matrix = {{
    {1, 0, 0, 0},
    {v.y, 1, 0, 0},
    {v.z, 0, 1, 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_shear_y(TransformF *transform, Vec3f v) {
  Matrix_4x4f matrix = {{
    {1, v.x, 0, 0},
    {0, 1, 0, 0},
    {0, v.z, 1, 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_shear_z(TransformF *transform, Vec3f v) {
  Matrix_4x4f matrix = {{
    {1, 0, v.x, 0},
    {0, 1, v.y, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_rotate_x(TransformF *transform, AngleRad angle) {
  Matrix_4x4f matrix = {{
    {1, 0, 0, 0},
    {0, cosf(angle), -sinf(angle), 0},
    {0, sinf(angle), cosf(angle), 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_rotate_y(TransformF *transform, AngleRad angle) {
  Matrix_4x4f matrix = {{
    {cosf(angle), 0, sinf(angle), 0},
    {0, 1, 0, 0},
    {-sinf(angle), 0, cosf(angle), 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_rotate_z(TransformF *transform, AngleRad angle) {
  Matrix_4x4f matrix = {{
    {cosf(angle), -sinf(angle), 0, 0},
    {sinf(angle), cosf(angle), 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4f_multiply(transform, &matrix);
}

void transform_f_vec4f(TransformF *transform, Vec4f *v) {
  for (int i=0; i<4; i++) {
    float a = ((float*)&v->x)[i];
    ((float*)&v->x)[i] = 0; // :troll:

    for (int j=0; j<4; j++) {
      ((float*)&v->x)[i] += transform->m[i][0] * a;
    }
  }
}

// Double //
void transform_d_translate(TransformD *transform, Vec3d offset) {
  Matrix_4x4d matrix;
  matrix_4x4d_identity(&matrix);

  matrix.m[0][3] = offset.x;
  matrix.m[1][3] = offset.y;
  matrix.m[2][3] = offset.z;

  matrix_4x4d_multiply(transform, &matrix);
}

void transform_d_scale_sc(TransformD *transform, double scalar) {
  Matrix_4x4d matrix;
  matrix_4x4d_identity(&matrix);

  matrix.m[0][0] = scalar;
  matrix.m[1][1] = scalar;
  matrix.m[2][2] = scalar;

  matrix_4x4d_multiply(transform, &matrix);
}

void transform_d_scale_ve(TransformD *transform, Vec3d scale) {
  Matrix_4x4d matrix;
  matrix_4x4d_identity(&matrix);

  matrix.m[0][0] = scale.x;
  matrix.m[1][1] = scale.y;
  matrix.m[2][2] = scale.z;

  matrix_4x4d_multiply(transform, &matrix);
}

void transform_d_shear_x(TransformD *transform, Vec3d v) {
  Matrix_4x4d matrix = {{
    {1, 0, 0, 0},
    {v.y, 1, 0, 0},
    {v.z, 0, 1, 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4d_multiply(transform, &matrix);
}

void transform_d_shear_y(TransformD *transform, Vec3d v) {
  Matrix_4x4d matrix = {{
    {1, v.x, 0, 0},
    {0, 1, 0, 0},
    {0, v.z, 1, 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4d_multiply(transform, &matrix);
}

void transform_d_shear_z(TransformD *transform, Vec3d v) {
  Matrix_4x4d matrix = {{
    {1, 0, v.x, 0},
    {0, 1, v.y, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4d_multiply(transform, &matrix);
}

void transform_d_rotate_x(TransformD *transform, AngleRad angle) {
  Matrix_4x4d matrix = {{
    {1, 0, 0, 0},
    {0, cos(angle), -sin(angle), 0},
    {0, sin(angle), cos(angle), 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4d_multiply(transform, &matrix);
}

void transform_d_rotate_y(TransformD *transform, AngleRad angle) {
  Matrix_4x4d matrix = {{
    {cos(angle), 0, sin(angle), 0},
    {0, 1, 0, 0},
    {-sin(angle), 0, cos(angle), 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4d_multiply(transform, &matrix);
}

void transform_d_rotate_z(TransformD *transform, AngleRad angle) {
  Matrix_4x4d matrix = {{
    {cos(angle), -sin(angle), 0, 0},
    {sin(angle), cos(angle), 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }};

  matrix_4x4d_multiply(transform, &matrix);
}

void transform_d_vec4d(TransformD *transform, Vec4d *v) {
  for (int i=0; i<4; i++) {
    double a = ((double*)&v->x)[i];
    ((double*)&v->x)[i] = 0;

    for (int j=0; j<4; j++) {
      ((double*)&v->x)[i] += transform->m[i][0] * a;
    }
  }
}
