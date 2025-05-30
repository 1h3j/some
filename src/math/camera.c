#include "math/camera.h"
#include "math/angles.h"
#include "math/matrix.h"
#include "math/transform.h"
#include "math/vectors.h"
#include "math/projection.h"
#include "render/shader.h"
#include <stdlib.h>

void camera_calculate_matrices(Camera *camera) {
  matrix_4x4f_identity(&camera->projection_matrix);
  matrix_4x4f_identity(&camera->view_matrix);

  const Vec3f zero_vector = (Vec3f){ 0, 0, 0 };

  transform_f_rotate_x(&camera->view_matrix, degrees_to_radians(camera->rotation.pitch));
  transform_f_rotate_y(&camera->view_matrix, degrees_to_radians(camera->rotation.yaw));
  transform_f_translate(&camera->view_matrix, vec3_sub(Vec3f, zero_vector, camera->position));

  const float front = camera->clip_near;
  const float back = camera->clip_far;

  const float aspect_ratio = (float)camera->width / camera->height;

  // TODO: Finish orthographic projection
  if (camera->projection_type == PROJECTION_TYPE_PERSPECTIVE) {
    float tangent, top, right;

    tangent = tan(degrees_to_radians(camera->field_of_view) / 2);

    if (aspect_ratio > 1) {
      top = front * tangent;
      right = top * aspect_ratio;
    } else {
      right = front * tangent;
      top = right / aspect_ratio;
    }

    projection_perspective_symmetrical(&camera->projection_matrix, right * 2, top * 2, front, back);
  } else {
    float rprism_w = aspect_ratio / camera->zoom;
    float rprism_h = 1.f / camera->zoom;

    projection_orthographic_symmetrical(&camera->projection_matrix, rprism_w, rprism_h, front, back);
  }
}

Camera *camera_create(int width, int height) {
  Camera *camera = (Camera *)malloc(sizeof(Camera));

  camera->width = width;
  camera->height = height;

  camera->position = (Vec3f){0, 0, 0};
  camera->rotation = (Rotation3f){0, 0, 0};

  camera->field_of_view = 60;
  camera->zoom = 1.f / 2.f;
  camera->projection_type = PROJECTION_TYPE_PERSPECTIVE;
  camera->clip_near = 0.1;
  camera->clip_far = 100.f;

  return camera;
}

inline void camera_free(Camera *camera) {
  free(camera);
}

inline void camera_set_shader_matrices(Camera *camera, Shader *shader,
                                const char* view_mat_name, const char* proj_mat_name) {
  shader_uniform_mat4x4f(shader, view_mat_name, &camera->view_matrix);
  shader_uniform_mat4x4f(shader, proj_mat_name, &camera->projection_matrix);
}
