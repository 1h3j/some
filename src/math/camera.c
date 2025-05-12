#include "math/camera.h"
#include "math/matrix.h"
#include "math/transform.h"
#include "math/vectors.h"
#include <stdlib.h>

void camera_calculate_matrices(struct camera_t *camera) {
  matrix_4x4f_identity(&camera->view_matrix);
  transform_fl_rotate_x(&camera->view_matrix, camera->rotation.pitch);
  transform_fl_rotate_y(&camera->view_matrix, camera->rotation.yaw);
  transform_fl_translate(&camera->view_matrix,
                         vec3_scale(struct vec3f_t, camera->position, -1.0f));

  if (camera->projection_type == PROJECTION_TYPE_ORTHO) {
    // clang-format off
    struct matrix_4x4f_t *proj = &camera->projection_matrix;
    matrix_4x4f_identity(proj);

    float aspect_ratio = (float)camera->width / (float)camera->height;

    struct vec2f_t ortho_plane_size = {
      camera->zoom * ((camera->width > camera->height) ? 1.f : aspect_ratio),
      camera->zoom * ((camera->width < camera->height) ? 1.f : aspect_ratio)
    };

    float left  = -ortho_plane_size.x / 2.f;
    float right = ortho_plane_size.x / 2.f;

    float bottom = -ortho_plane_size.y / 2.f;
    float top    = ortho_plane_size.y / 2.f;

    float m[4][4] = {
      {2.f / (right - left), 0, 0, -(right + left) / (right - left)}, 
      {0, 2.f / (top - bottom), 0, -(top + bottom) / (top - bottom)}, 
      {0, 0, -2 / (camera->clip_far - camera->clip_near), -(camera->clip_far + camera->clip_near) / (camera->clip_far - camera->clip_near)}, 
      {0, 0, 0, 1}
    };
    // clang-format on
  }
}

struct camera_t *create_camera(int width, int height) {
  struct camera_t *camera = (struct camera_t *)malloc(sizeof(struct camera_t));

  camera->width = width;
  camera->height = height;

  camera->position = (struct vec3f_t){0, 0, 0};
  camera->rotation = (struct rotation_t){0, 0, 0};

  return camera;
}
