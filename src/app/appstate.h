#ifndef APPSTATE_H
#define APPSTATE_H

#include "resources.h"
#include <SDL3/SDL_video.h>

typedef struct {
  SDL_Window* window;
  struct renderer_t *renderer;
  resource_stack_t *resources;

  enum {
    APPSTATUS_CONTINUE,
    APPSTATUS_EXIT_SUCCESS,
    APPSTATUS_EXIT_FAILURE,
  } appstatus_e;
} appstate_t;

#endif // APPSTATE_H
