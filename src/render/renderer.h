#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL_video.h>

#include "math/camera.h"
#include "math/vectors.h"
#include "render/shader.h"

#include <glad/glad.h>

struct line_t {
  struct vec3d_t start, end;
  struct vec4f_t color;
  float width;
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

  struct camera_t camera;

  unsigned int line_vao, quad_vao, cube_vao;
  unsigned int line_vbo, quad_vbo, cube_vbo;
  unsigned int quad_ebo, cube_ebo;
};

void renderer_set_shader(struct renderer_t *renderer, struct shader_t *shader);

struct renderer_t *create_renderer(SDL_Window *window);

void init_renderer(struct renderer_t *renderer);

void free_renderer(struct renderer_t *renderer);

void renderer_line(struct renderer_t *renderer, struct line_t line);

#endif // !RENDERER_H
