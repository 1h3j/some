#include "render/renderer.h"
#include "glad/glad.h"
#include "math/matrix.h"
#include "math/vectors.h"
#include "render/shader.h"
#include <stdlib.h>

struct renderer_t *renderer_create(SDL_Window *window) {
  struct renderer_t *renderer =
      (struct renderer_t *)malloc(sizeof(struct renderer_t));
  renderer->context = SDL_GL_CreateContext(window);

  return renderer;
}


void renderer_initialize(struct renderer_t *renderer) {
  renderer->default_2d = create_shader(RENDERER_2D_DEFAULT_VSH_S, RENDERER_2D_DEFAULT_FSH_S);
  renderer->default_3d = create_shader(RENDERER_3D_DEFAULT_VSH_S, RENDERER_3D_DEFAULT_FSH_S);

  glGenVertexArrays(3, &renderer->line_vao);
  glGenBuffers(3, &renderer->line_vbo);

  // Line
  glBindVertexArray(renderer->line_vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->line_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec3f_t) * 2, NULL,
               GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vec3f_t),
                        (void *)0);
  glEnableVertexAttribArray(0);

  // Quad
  glBindVertexArray(renderer->quad_vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->quad_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec3f_t) * 4, NULL,
               GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vec3f_t),
                        (void *)0);
  glEnableVertexAttribArray(0);

  // Cube
  glBindVertexArray(renderer->cube_vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->cube_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec3f_t) * 8, NULL,
               GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vec3f_t),
                        (void *)0);
  glEnableVertexAttribArray(0);
}


void renderer_free(struct renderer_t *renderer) {
  SDL_GL_DestroyContext(renderer->context);

  glDeleteVertexArrays(3, &renderer->line_vao);
  glDeleteBuffers(3, &renderer->line_vbo);
  free_shader(renderer->default_2d);
  free_shader(renderer->default_3d);

  free(renderer);
}


void renderer_line(struct renderer_t *renderer, struct line_t line) {
  glBindVertexArray(renderer->line_vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->line_vbo);

  struct vec3f_t buffer[2] = {
    line.start,
    line.end
  };

  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(struct vec3f_t) * 2, buffer); 

  shader_uniform_vec4f(renderer->default_2d, "color", line.color);
  shader_use(renderer->default_2d);

  glLineWidth(line.width);
  glDrawArrays(GL_LINES, 0, 2);

  glBindVertexArray(0);
}


void renderer_quad(struct renderer_t *renderer, struct quad_t quad) {
  glBindVertexArray(renderer->quad_vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->quad_vbo);

  struct vec3f_t avg_point = {
    (quad.q1.x + quad.q2.x + quad.q3.x + quad.q4.x) / 4.f,
    (quad.q1.y + quad.q2.y + quad.q3.y + quad.q4.y) / 4.f,
    (quad.q1.z + quad.q2.z + quad.q3.z + quad.q4.z) / 4.f
  };

  struct vec3f_t buffer[4] = {
    quad.q2, 
    quad.q3, 
    quad.q1, 
    quad.q4, 
  };

  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(struct vec3f_t) * 4, buffer); 

  shader_uniform_vec4f(renderer->default_2d, "color", quad.color);
  shader_use(renderer->default_2d);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glBindVertexArray(0);
}


void renderer_set_shader(struct renderer_t *renderer, struct shader_t *shader) {
  renderer->current_shader = shader;
  glUseProgram(shader->program);
}


void renderer_fill(struct vec4f_t color, GLbitfield clear_mask) {
  glClearColor(color.x, color.y, color.z, color.w);
  glClear(clear_mask);
}
