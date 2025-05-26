#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL_video.h>

#include "util/array.h"
#include "math/camera.h"
#include "math/vectors.h"
#include "util/hashmap.h"
#include "render/shader.h"

#include <glad/glad.h>

#define RENDERER_2D_DEFAULT_VSH_S "#version 330\nlayout (location = 0) in vec3 aPos;\nlayout (location = 1) in vec4 color;\nlayout (location = 2) in float lwidth;\nuniform mat4 model = mat4(1);\nout vec4 vColor;\nvoid main() { gl_Position = model * vec4(aPos, 1.0); vColor = color; gl_LineWidth = lwidth; }"
#define RENDERER_2D_DEFAULT_FSH_S "#version 330\nin vec4 vColor;\nout vec4 fragmentColor;\nvoid main() { fragmentColor = vColor; }"

#define RENDERER_3D_DEFAULT_VSH_S "#version 330\nlayout (location = 0) in vec3 aPos;\nuniform mat4 model = mat4(1);\nuniform mat4 view;\nuniform mat4 projection;\nvoid main() { gl_Position = projection * view * model * vec4(aPos, 1.0); }"
#define RENDERER_3D_DEFAULT_FSH_S "#version 330\nuniform vec4 color;\nout vec4 fragmentColor;\nvoid main() { fragmentColor = color; fragmentColor *= gl_FrontFacing ? 1 : 0.5; }"

#if !defined(RENDERING_QUEUE_MAX_INSTANCES)
#define RENDERING_QUEUE_MAX_INSTANCES 4
#endif

struct render_queue_entry_t {
  unsigned int offset, end;
};

struct triangle_t {
  struct vec3f_t v1, v2, v3;
  struct vec4f_t color;
};

struct line_t {
  struct vec3f_t start, end;
  struct vec4f_t color;
  float width;
};
struct rect_t {
  struct vec3f_t start, end;
  struct vec4f_t color;
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

  map_t *shader_instances_map;
  array_t *sim_shaders_array;

  bool enable_render_queue;

  unsigned int tri_instances;
  unsigned int line_instances;
  unsigned int quad_instances;
  unsigned int cube_instances;

  unsigned int tri_vao, line_vao, quad_vao, cube_vao;
  unsigned int tri_vbo, line_vbo, quad_vbo, cube_vbo;
  unsigned int tri_col_vbo, line_col_width_vbo, quad_col_vbo, cube_col_vbo;
};

/**
 * Changes current_shader. This does not call shader_use.
 *
 * @param renderer Pointer to a renderer
 * @param shader   Pointer to a shader object
*/
void renderer_set_shader(struct renderer_t *renderer, struct shader_t *shader);

/**
 * Allocates a renderer and assigns an OpenGL context to it.
 *
 * @param window An SDL Window to put the context in
 * @return A pointer to the allocated renderer
*/
struct renderer_t *renderer_create(SDL_Window *window);

/**
 * Initializes renderer resources
 *
 * @param renderer Pointer to an allocated renderer
*/
void renderer_initialize(struct renderer_t *renderer);

/**
 * Frees the resources associated with the particular renderer.
 *
 * @param renderer Pointer to a renderer
*/
void renderer_free(struct renderer_t *renderer);

/**
 * Draws a line to the renderer
 *
 * @param renderer Pointer to a renderer
 * @param line     A line object
*/
void renderer_line(struct renderer_t *renderer, struct line_t line);

/**
 * Draws a quad to the renderer
 *
 * @param renderer Pointer to a renderer
 * @param quad     A quad object
*/
void renderer_quad(struct renderer_t *renderer, struct quad_t quad);

/**
 * Draws a 3d rectangle to the renderer
 *
 * @param renderer Pointer to a renderer
 * @param rect     A rectangle object
*/
void renderer_rect(struct renderer_t *renderer, struct rect_t rect, bool cull_faces);

/**
 * Draws a triangle to the renderer
 *
 * @param renderer Pointer to a renderer
 * @param triangle A triangle object
*/
void renderer_triangle(struct renderer_t *renderer, struct triangle_t triangle);

/**
 * Fills the context with a color.
 *
 * @param color
 * @param clear_mask A bunch of flags OR'ed together. Recommended value is GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
*/
void renderer_fill(struct vec4f_t color, GLbitfield clear_mask);

/*
 * Start drawing the rendering queue, then clear it.
 *
 * @param renderer Pointer to a renderer
*/
void renderer_start_drawing(struct renderer_t *renderer);

#endif // !RENDERER_H
