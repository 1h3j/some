#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL_video.h>
#include <glad/glad.h>

#include "shader.h"

#define RENDERER_2D_DEFAULT_VSH_S "#version 330\nlayout (location = 0) in vec3 aPos;\nlayout (location = 1) in vec4 color;\nuniform mat4 model = mat4(1);\nout vec4 vColor;\nvoid main() { gl_Position = model * vec4(aPos, 1.0); vColor = color; }"
#define RENDERER_2D_DEFAULT_FSH_S "#version 330\nin vec4 vColor;\nout vec4 fragmentColor;\nvoid main() { fragmentColor = vColor; }"

#define RENDERER_3D_DEFAULT_VSH_S "#version 330\nlayout (location = 0) in vec3 aPos;\nlayout (location = 1) in vec4 color;\nuniform mat4 model = mat4(1);\nuniform mat4 view;\nuniform mat4 projection;\nout vec4 vColor;\nvoid main() { gl_Position = projection * view * model * vec4(aPos, 1.0); vColor = color; }"
#define RENDERER_3D_DEFAULT_FSH_S "#version 330\nin vec4 vColor;\nout vec4 fragmentColor;\nvoid main() { fragmentColor = vColor; }"

typedef struct {
  SDL_GLContext gl;
  SDL_Window *window;
  Shader *selected_shader;
} Renderer;

/**
 * Allocate a new renderer object and then open a new OpenGL context.
 *
 * @param window An SDL window
 * @return Pointer to the allocated renderer.
*/
Renderer *renderer_create(SDL_Window* window);

/**
 * Deallocates resources used by the renderer and destroyes the OpenGL context with it.
 *
 * @param renderer Renderer object
*/
void renderer_destroy(Renderer* renderer);

/**
 * Switch the current OpenGL context
 *
 * @param renderer Renderer to switch to.
*/
void renderer_switch(Renderer *renderer);

/**
 * Clears color buffer with a specified color.
 *
 * @param color Color in normalized floating point RGBA
*/
void render_clear(Vec4f color);

/**
 * Clears color buffer with a specified color, aswell as the depth buffer.
 *
 * @param color Color in normalized floating point RGBA
*/
void render_clear_with_depth(Vec4f color);

#endif // !RENDERER_H
