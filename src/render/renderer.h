#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL_video.h>

#include "math/camera.h"
#include "math/vectors.h"
#include "render/shader.h"

#include <glad/glad.h>

#define RENDERER_2D_DEFAULT_VSH_S "#version 330\nlayout (location = 0) in vec3 aPos;\nvoid main() { gl_Position = vec4(aPos, 1.0); }"
#define RENDERER_2D_DEFAULT_FSH_S "#version 330\nuniform vec4 color;\nout vec4 fragmentColor;\nvoid main() { fragmentColor = color; }"

#define RENDERER_3D_DEFAULT_VSH_S "#version 330\nlayout (location = 0) in vec3 aPos;\nuniform mat4 model;\nuniform mat4 view;\nuniform mat4 projection;\nvoid main() { gl_Position = projection * view * model * vec4(aPos, 1.0); }"
#define RENDERER_3D_DEFAULT_FSH_S "#version 330\nuniform vec4 color;\nout vec4 fragmentColor;\nvoid main() { fragmentColor = color; }"

struct line_t {
  struct vec3f_t start, end;
  struct vec4f_t color;
  float width;
};

struct quad_t {
  struct vec3f_t q1, q2, q3, q4;
  struct vec4f_t color;
};

struct path_t {
  struct vec3d_t *points;
  struct vec4f_t color;
  int segments;
  float width;
};

struct renderer_t {
  SDL_GLContext context;
  struct shader_t *current_shader;

  struct shader_t *default_3d;
  struct shader_t *default_2d;

  struct camera_t camera;

  unsigned int line_vao, quad_vao, cube_vao;
  unsigned int line_vbo, quad_vbo, cube_vbo;
};

void renderer_set_shader(struct renderer_t *renderer, struct shader_t *shader);

struct renderer_t *renderer_create(SDL_Window *window);

void renderer_initialize(struct renderer_t *renderer);

void renderer_free(struct renderer_t *renderer);

void renderer_line(struct renderer_t *renderer, struct line_t line);

void renderer_quad(struct renderer_t *renderer, struct quad_t quad);

void renderer_fill(struct vec4f_t color, GLbitfield clear_mask);

#endif // !RENDERER_H
