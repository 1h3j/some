#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include <math.h>
#define USE_EVENT_CALLBACKS

#include "util/logging.h"
#include "render/renderer.h"
#include "event/events.h"
#include "event/callback.h"
#include "app/appstate.h"

#include <SDL3/SDL.h>

on_event(EVENT_TYPE_SDL_EVENT, {
  SDL_Event *ev = event->sdl_event;
  appstate_t *state = (appstate_t *)event->appstate;

  if (ev->type == SDL_EVENT_QUIT) {
    state->appstatus_e = APPSTATUS_EXIT_SUCCESS;
  }
})

on_event(EVENT_TYPE_RENDER_EVENT, {
  struct renderer_t *render = event->renderer;
  appstate_t *state = (appstate_t *)event->appstate;

  float time = SDL_GetTicks() / 1000.f;

  renderer_fill((struct vec4f_t){0.0f, 0.1f, 0.2f, 1.0f}, 
                GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  renderer_line(render, (struct line_t){
    {0, 0, 1},
    {1, 0, 1},

    {0.7f, 0.7f, 0.9f, 1.f},
    5
  });

  renderer_quad(render, (struct quad_t){
         { .5, -.5, 0},
         {-.5, -.5, 0},
         {-.5,  .5, 0},
         { .5,  .5, 0},

         {1.f, 1.f, 1.f, 1.f}
  });
})
