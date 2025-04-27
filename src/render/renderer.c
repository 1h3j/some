#include "render/renderer.h"
#include "glad/glad.h"
#include "math/matrix.h"
#include "render/shader.h"
#include <stdlib.h>

struct renderer_t *create_renderer(SDL_Window *window) {
  struct renderer_t *renderer =
      (struct renderer_t *)malloc(sizeof(struct renderer_t));
  renderer->context = SDL_GL_CreateContext(window);

  return renderer;
}

void init_renderer(struct renderer_t *renderer) {
  glGenVertexArrays(3, &renderer->line_vao);
  glGenBuffers(3, &renderer->line_vbo);
  glGenBuffers(2, &renderer->quad_ebo);

  struct vec3f_t line_data[2] = {{0, 0, 0}, {0, 1, 0}};

  // Line
  glBindVertexArray(renderer->line_vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->line_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec3f_t) * 2, line_data,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vec3d_t),
                        (void *)0);
  glEnableVertexAttribArray(0);

  // Quad
  glBindVertexArray(renderer->line_vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->line_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec3f_t) * 4, NULL,
               GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vec3d_t),
                        (void *)0);
  glEnableVertexAttribArray(0);

  // Cube
  glBindVertexArray(renderer->line_vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->line_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec3f_t) * 8, NULL,
               GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vec3d_t),
                        (void *)0);
  glEnableVertexAttribArray(0);
}

void free_renderer(struct renderer_t *renderer) {
  SDL_GL_DestroyContext(renderer->context);

  glDeleteVertexArrays(3, &renderer->line_vao);
  glDeleteBuffers(3, &renderer->line_vbo);
  glDeleteBuffers(2, &renderer->quad_ebo);

  free(renderer);
}

void renderer_line(struct renderer_t *renderer, struct line_t line) {
  struct matrix_4x4f_t model;
  matrix_4x4f_identity(&model);

  model.m[0][0] = line.end.x - line.start.x;
  model.m[1][0] = line.end.y - line.start.y;
  model.m[2][0] = line.end.z - line.start.z;

  model.m[1][3] = line.start.x;
  model.m[2][3] = line.start.y;
  model.m[3][3] = line.start.z;

  shader_uniform_vec4f(renderer->current_shader, "color", line.color);
  shader_uniform_mat4x4f(renderer->current_shader, "model", &model);

  glBindVertexArray(renderer->line_vao);
  glLineWidth(line.width);
  glDrawArrays(GL_LINES, 0, 2);
}

void renderer_set_shader(struct renderer_t *renderer, struct shader_t *shader) {
  renderer->current_shader = shader;
  glUseProgram(shader->program);
}
