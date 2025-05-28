#include "render/renderer.h"
#include "glad/glad.h"

#include <SDL3/SDL_video.h>
#include <stdlib.h>

Renderer *renderer_create(SDL_Window *window) {
  Renderer *r = (Renderer *) malloc(sizeof(Renderer));
  memset(r, 0, sizeof(Renderer));
  
  r->window = window;
  r->gl = SDL_GL_CreateContext(window);

  return r;
}

void renderer_destroy(Renderer *renderer) {
  SDL_GL_DestroyContext(renderer->gl);
  free(renderer);
}

void renderer_switch(Renderer *renderer) {
  SDL_GL_MakeCurrent(renderer->window, renderer->gl);
}

void render_clear(Vec4f color) {
  glClearColor(color.x, color.y, color.z, color.w);
  glClear(GL_COLOR_BUFFER_BIT);
}

void render_clear_with_depth(Vec4f color) {
  glClearColor(color.x, color.y, color.z, color.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
