#include "math/angles.h"
#include "math/camera.h"
#include "math/matrix.h"
#include "render/shader.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#define USE_EVENT_CALLBACKS

#include "render/renderer.h"
#include "math/transform.h"
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

  render->camera.projection_type = PROJECTION_TYPE_PERSPECTIVE;
  render->camera.position.z = 2;
  render->camera.field_of_view = 110;

  renderer_set_shader(render, render->default_3d);

  struct matrix_4x4f_t model;
  matrix_4x4f_identity(&model);

  transform_fl_rotate_y(&model, degrees_to_radians(time * 45));
  transform_fl_rotate_x(&model, degrees_to_radians(time * 180));

  shader_uniform_mat4x4f(render->current_shader, "model", &model);
  shader_uniform_mat4x4f(render->current_shader, "view", &render->camera.view_matrix);
  shader_uniform_mat4x4f(render->current_shader, "projection", &render->camera.projection_matrix);

  renderer_quad(render, (struct quad_t){
         {-1, -1, 0},
         { 1, -1, 0},
         { 1,  1, 0},
         {-1,  1, 0},

         {1.f, 1.f, 1.f, 1.f}
  });
  renderer_quad(render, (struct quad_t){
         {0, -1, -1},
         {0,  1, -1},
         {0,  1,  1},
         {0, -1,  1},

         {1.f, 1.f, 1.f, 1.f}
  });
})
