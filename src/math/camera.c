#include "math/camera.h"
#include "math/angles.h"
#include "math/matrix.h"
#include "math/transform.h"
#include "math/vectors.h"
#include "math/projection.h"
#include <stdlib.h>

void camera_calculate_matrices(struct camera_t *camera) {
  matrix_4x4f_identity(&camera->projection_matrix);
  matrix_4x4f_identity(&camera->view_matrix);

  const struct vec3f_t zero_vector = (struct vec3f_t){ 0, 0, 0 };

  transform_f_rotate_x(&camera->view_matrix, degrees_to_radians(camera->rotation.pitch));
  transform_f_rotate_y(&camera->view_matrix, degrees_to_radians(camera->rotation.yaw));
  transform_f_translate(&camera->view_matrix, vec3_sub(struct vec3f_t, zero_vector, camera->position));

  const float front = camera->clip_near;
  const float back = camera->clip_far;

  const float aspect_ratio = (float)camera->width / camera->height;

  if (camera->projection_type == PROJECTION_TYPE_PERSPECTIVE) {
    float tangent, top, right, left, bottom;

    tangent = tan(degrees_to_radians(camera->field_of_view) / 2);

    if (aspect_ratio > 1) {
      top = front * tangent;
      right = top * aspect_ratio;
    } else {
      right = front * tangent;
      top = right / aspect_ratio;
    }

    left = -right;
    bottom = -top;

    projection_perspective(&camera->projection_matrix, left, right, bottom, top, front, back);
  }
}

struct camera_t *camera_create(int width, int height) {
  struct camera_t *camera = (struct camera_t *)malloc(sizeof(struct camera_t));

  camera->width = width;
  camera->height = height;

  camera->position = (struct vec3f_t){0, 0, 0};
  camera->rotation = (struct rotation_t){0, 0, 0};

  return camera;
}
