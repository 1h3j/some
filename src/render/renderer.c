#include "render/renderer.h"
#include "glad/glad.h"
#include "math/vectors.h"
#include "render/shader.h"
#include "util/array.h"
#include "util/logging.h"
#include "util/hashmap.h"
#include <stddef.h>
#include <stdlib.h>

uint64_t nohash(uint64_t b, void* k, int k_l) {
  uint64_t a;

  if (k_l < sizeof(uint64_t)) {
    memcpy(&a, k, k_l);
  } else {
    a = *(uint64_t *) k;
  }

  return a;
}

struct renderer_t *renderer_create(SDL_Window *window) {
  struct renderer_t *renderer =
      (struct renderer_t *)malloc(sizeof(struct renderer_t));
  renderer->context = SDL_GL_CreateContext(window);

  renderer->sim_shaders_array = array_create(struct shader_t *, 128);

  return renderer;
}


void renderer_initialize(struct renderer_t *renderer) {
  renderer->default_2d = create_shader(RENDERER_2D_DEFAULT_VSH_S, RENDERER_2D_DEFAULT_FSH_S);
  renderer->default_3d = create_shader(RENDERER_3D_DEFAULT_VSH_S, RENDERER_3D_DEFAULT_FSH_S);

  unsigned int d = 0;
  d_map_set(renderer->shader_instances_map, renderer->default_2d->program, &d);
  array_append_back(renderer->sim_shaders_array, renderer->default_2d);

  d_map_set(renderer->shader_instances_map, renderer->default_3d->program, &d);
  array_append_back(renderer->sim_shaders_array, renderer->default_3d);

  glGenVertexArrays(1, &renderer->tri_vao);
  glGenBuffers(1, &renderer->tri_vbo);

  glGenVertexArrays(1, &renderer->line_vao);
  glGenBuffers(1, &renderer->line_vbo);

  glGenVertexArrays(1, &renderer->quad_vao);
  glGenBuffers(1, &renderer->quad_vbo);
  
  glGenVertexArrays(1, &renderer->cube_vao);
  glGenBuffers(1, &renderer->cube_vbo);

  // Triangles
  glBindVertexArray(renderer->tri_vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->tri_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec3f_t) * 3 * RENDERING_QUEUE_MAX_INSTANCES, NULL,
               GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vec3f_t),
                        (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, renderer->tri_col_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec4f_t) * RENDERING_QUEUE_MAX_INSTANCES, NULL,
               GL_DYNAMIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(struct vec4f_t),
                        (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribDivisor(1, 1);

  // Lines
  glBindVertexArray(renderer->line_vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->line_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec3f_t) * 2 * RENDERING_QUEUE_MAX_INSTANCES, NULL,
               GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vec3f_t),
                        (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, renderer->line_col_width_vbo);
  glBufferData(GL_ARRAY_BUFFER, (sizeof(struct vec4f_t) + sizeof(float)) * RENDERING_QUEUE_MAX_INSTANCES, NULL,
               GL_DYNAMIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(struct vec4f_t) + sizeof(float),
                        (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribDivisor(1, 1);

  glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(struct vec4f_t) + sizeof(float),
                        (void *) sizeof(struct vec4f_t));
  glEnableVertexAttribArray(2);
  glVertexAttribDivisor(2, 1);

  // Quad
  glBindVertexArray(renderer->quad_vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->quad_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec3f_t) * 4 * RENDERING_QUEUE_MAX_INSTANCES, NULL,
               GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vec3f_t),
                        (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, renderer->quad_col_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec4f_t) * RENDERING_QUEUE_MAX_INSTANCES, NULL,
               GL_DYNAMIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(struct vec4f_t),
                        (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribDivisor(1, 1);

  // Cube
  glBindVertexArray(renderer->cube_vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->cube_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec3f_t) * 8 * RENDERING_QUEUE_MAX_INSTANCES, NULL,
               GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vec3f_t),
                        (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, renderer->cube_col_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec4f_t) * RENDERING_QUEUE_MAX_INSTANCES, NULL, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(struct vec4f_t),
                        (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribDivisor(1, 1);
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

  const size_t line_b = sizeof(struct line_t);
  glBufferSubData(GL_ARRAY_BUFFER, renderer->line_instances * line_b, line_b, &line); 

  if (renderer->enable_render_queue) {
    renderer->line_instances++;
    return;
  }

  if (renderer->current_shader == NULL) {
    shader_use(renderer->default_2d);
  } else {
    shader_use(renderer->current_shader);
  }

  // glLineWidth(line.width);
  glEnable(GL_LINE_WIDTH);
  glDrawArrays(GL_LINES, 0, 2);

  glBindVertexArray(0);
}


void renderer_triangle(struct renderer_t *renderer, struct triangle_t triangle) {
  glBindVertexArray(renderer->tri_vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->tri_vbo);

  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(struct vec3f_t) * 3, &triangle.v1);

  shader_uniform_vec4f(renderer->default_2d, "color", triangle.color);
  shader_use(renderer->default_2d);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glBindVertexArray(0);
}


//  TODO: Have it account for all directions not just the z-axis (use normals)

void renderer_quad(struct renderer_t *renderer, struct quad_t quad) {
  glBindVertexArray(renderer->quad_vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->quad_vbo);

  struct vec3f_t avg_point = {
    (quad.q1.x + quad.q2.x + quad.q3.x + quad.q4.x) / 4.f,
    (quad.q1.y + quad.q2.y + quad.q3.y + quad.q4.y) / 4.f,
    (quad.q1.z + quad.q2.z + quad.q3.z + quad.q4.z) / 4.f
  };

  struct vec3f_t buffer[4];

  for (int i=0; i<4; i++) {
    struct vec3f_t rel_point = vec3_sub(struct vec3f_t, (&quad.q1)[i], avg_point);
    if      (rel_point.x >= 0 && rel_point.y >= 0) buffer[2] = (&quad.q1)[i]; // Q1
    else if (rel_point.x <  0 && rel_point.y >= 0) buffer[0] = (&quad.q1)[i]; // Q2
    else if (rel_point.x <  0 && rel_point.y <  0) buffer[1] = (&quad.q1)[i]; // Q3
    else if (rel_point.x >= 0 && rel_point.y <  0) buffer[3] = (&quad.q1)[i]; // Q4
  }

  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(struct vec3f_t) * 4, buffer); 

  if (renderer->current_shader == NULL) {
    shader_uniform_vec4f(renderer->default_2d, "color", quad.color);
    shader_use(renderer->default_2d);
  } else {
    shader_uniform_vec4f(renderer->current_shader, "color", quad.color);
    shader_use(renderer->current_shader);
  }

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glBindVertexArray(0);
}

// PERF : Add culling
// Explanation: 
//   You can only see 1-3 sides of a cube at a time.
//   By using triangle fans, it's much easier to render
//   the cube than by using triangle strips.
//        _ C _
//     _--  |  --_
//  B/H_    |    _ D 
//   |  --_ | _--  |
//   |    _ A _    |
//   | _--  |  --_ |
//   G _    |    _ E 
//      --_ | _-- 
//          F 

void renderer_rect(struct renderer_t *renderer, struct rect_t rect, bool cull_faces) {
  glBindVertexArray(renderer->cube_vao);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->cube_vbo);

  struct vec3f_t buffer[8] = {
    rect.start,
    {rect.start.x, rect.start.y, rect.end.z},
    {rect.end.x, rect.start.y, rect.end.z},
    {rect.end.x, rect.start.y, rect.start.z},

    {rect.start.x, rect.end.y, rect.start.z},
    {rect.start.x, rect.end.y, rect.end.z},
    rect.end,
    {rect.end.x, rect.end.y, rect.start.z}
  };

  unsigned int indices[] = {
    0, 4, 5, 0, 5, 1,
    0, 2, 1, 0, 3, 2,
    0, 4, 7, 0, 7, 3,
    5, 4, 7, 5, 7, 6,
    3, 7, 6, 3, 6, 2,
    1, 5, 6, 1, 6, 2
  };

  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(buffer), buffer);

  if (renderer->current_shader == NULL) {
    shader_uniform_vec4f(renderer->default_3d, "color", rect.color);
    shader_use(renderer->default_3d);
  } else {
    shader_uniform_vec4f(renderer->current_shader, "color", rect.color);
    shader_use(renderer->current_shader);
  }
 
  glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, indices);
  glBindVertexArray(0);
}

void renderer_set_shader(struct renderer_t *renderer, struct shader_t *shader) {
  renderer->current_shader = shader;
}

void renderer_clear_shader(struct renderer_t *renderer) {
  renderer->current_shader = NULL;
}

void renderer_fill(struct vec4f_t color, GLbitfield clear_mask) {
  glClearColor(color.x, color.y, color.z, color.w);
  glClear(clear_mask);
}

void renderer_start_drawing(struct renderer_t *renderer) {
  if (!renderer->enable_render_queue) {
    log_warn("Rendering queue is disabled, skipping...");
    return;
  }

  struct shader_t *shader;
  for (int i = 0; i < renderer->sim_shaders_array->allocated_length; i++) {
    shader = *(struct shader_t **) renderer->sim_shaders_array->array + i;
    shader_use(shader);


  }
}
