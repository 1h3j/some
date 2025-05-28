#ifndef APPSTATE_H
#define APPSTATE_H

#include "resources.h"
#include "render/renderer.h"

#include <SDL3/SDL_video.h>

typedef struct {
  SDL_Window* window;
  Renderer *renderer;
  resource_stack_t *resources;

  unsigned int width, height;

  enum {
    APPSTATUS_CONTINUE,
    APPSTATUS_EXIT_SUCCESS,
    APPSTATUS_EXIT_FAILURE,
  } appstatus_e;
} AppState;

#endif // APPSTATE_H
