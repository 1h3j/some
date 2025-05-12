#include "glad/glad.h"
#include "render/shader.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <stdlib.h>

#include "render/renderer.h"
#include "render/shader.h"
#include "util/logging.h"

#ifndef GL_MAJOR
#define GL_MAJOR 3
#endif // !GL_MAJ

#ifndef GL_MINOR
#define GL_MINOR 3
#endif // !GL_MIN

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 512
#endif // !WINDOW_WIDTH

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 512
#endif // !WINDOW_HEIGHT

struct appstate_t {
  SDL_Window *window;
  struct renderer_t *renderer;

  struct __resources_t {
    struct shader_t *shader_0;
    unsigned int test_vao, test_vbo;
  } resources;
};

void initialize_resources(struct __resources_t *r) {
}

void clean_resources(struct __resources_t *r) { free_shader(r->shader_0); }

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  *appstate = (void *)malloc(sizeof(struct appstate_t));
  struct appstate_t *state = (struct appstate_t *)(*appstate);

  if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
    log_error("SDL_InitSubSystem failed: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  log_info("SDL_InitSubSystem ran successfully");

  state->window = SDL_CreateWindow("Raycast Test", WINDOW_WIDTH, WINDOW_WIDTH,
                                   SDL_WINDOW_OPENGL);
  if (state->window == NULL) {
    log_fatal("SDL_CreateWindow failed: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  log_info("SDL_CreateWindow ran successfully");

  state->renderer = create_renderer(state->window);
  if (state->renderer->context == NULL) {
    log_fatal("SDL_GL_CreateContext failed");
    return SDL_APP_FAILURE;
  }

  SDL_GL_SetSwapInterval(1);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MINOR);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    log_error("Failed to initialize GLAD");
    return SDL_APP_FAILURE;
  }

  log_info("Running OpenGL %d.%d", GL_MAJOR, GL_MINOR);

  init_renderer(state->renderer);
  initialize_resources(&state->resources);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  struct appstate_t *state = (struct appstate_t *)appstate;

  glClearColor(0, 0.1, 0.2, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  SDL_GL_SwapWindow(state->window);
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  if (result == SDL_APP_SUCCESS) {
    struct appstate_t *state = (struct appstate_t *)appstate;

    free_renderer(state->renderer);
    SDL_DestroyWindow(state->window);
    log_info("Program finished successfully");
  } else if (result == SDL_APP_FAILURE) {
    log_fatal("Program finished unsuccessfully");
  }
}
