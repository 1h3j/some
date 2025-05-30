#ifndef CAMERA_H
#define CAMERA_H

#include "math/angles.h"
#include "math/matrix.h"
#include "math/vectors.h"

#include "render/shader.h"

typedef struct {
  int width, height;
  float clip_near, clip_far;
  float field_of_view;
  float zoom;

  Vec3f position;
  Rotation3f rotation;

  Matrix_4x4f view_matrix;
  Matrix_4x4f projection_matrix;

  enum {
    PROJECTION_TYPE_ORTHO,
    PROJECTION_TYPE_PERSPECTIVE
  } projection_type;
} Camera;

/**
 * Allocates a camera object.
 * 
 * @param width  Width of the display
 * @param height Height of the display
 * @return A camera object
*/
Camera *camera_create(int width, int height);

/**
 * Free resources used by camera
 *
 * @param camera Pointer to a camera object.
*/
void camera_free(Camera *camera);

/**
 * Calculate the view and projection matrices for use
 *
 * @param camera Pointer to a camera object
*/
void camera_calculate_matrices(Camera *camera);

/**
 * Set the shaders in a camera.
 *
 * @param camera        Camera object
 * @param shader        Shader object
 * @param view_mat_name Name of the view matrix inside the shader.
 * @param proj_mat_name Name of the projection matrix inside the shader.
*/
void camera_set_shader_matrices(Camera *camera, Shader *shader,
                                const char* view_mat_name, const char* proj_mat_name);

#endif // !CAMERA_H
