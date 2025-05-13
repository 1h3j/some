#ifndef CAMERA_H
#define CAMERA_H

#include "math/angles.h"
#include "math/matrix.h"
#include "math/vectors.h"

struct camera_t {
  int width, height;
  float clip_near, clip_far;
  float field_of_view;
  float zoom;

  struct vec3f_t position;
  struct rotation_t rotation;

  struct matrix_4x4f_t view_matrix;
  struct matrix_4x4f_t projection_matrix;

  enum __projection_type_e {
    PROJECTION_TYPE_ORTHO,
    PROJECTION_TYPE_PERSPECTIVE
  } projection_type;
};

struct camera_t *camera_create(int width, int height);

void camera_free(struct camera_t *camera);

void camera_calculate_matrices(struct camera_t *camera);

#endif // !CAMERA_H
