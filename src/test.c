#include "glad/glad.h"
#include "math/angles.h"
#include "math/camera.h"
#include "math/matrix.h"
#include "render/shader.h"
#include "render/renderer.h"
// #include "math/transform.h"
#include "event/events.h"
#include "event/callback.h"
#include "app/appstate.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>

struct vec2f_t saved_cursor_position;

on_event(EVENT_TYPE_INIT_EVENT, {
  appstate_t *state = (appstate_t *)event->appstate;
  struct renderer_t *render = state->renderer;

  render->camera.projection_type = PROJECTION_TYPE_PERSPECTIVE;
  render->camera.position.x = 2;
  render->camera.position.y = 2;
  render->camera.position.z = 2;
  render->camera.rotation.pitch = 45;
  render->camera.rotation.yaw = -45;
  render->camera.field_of_view = 90;

  glEnable(GL_DEPTH_TEST);
})


on_event(EVENT_TYPE_SDL_EVENT, {
  SDL_Event *ev = event->sdl_event;
  appstate_t *state = (appstate_t *)event->appstate;
  struct renderer_t *render = state->renderer;

  if (ev->type == SDL_EVENT_QUIT) {
    state->appstatus_e = APPSTATUS_EXIT_SUCCESS;
  } else if (ev->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    if (ev->button.button == SDL_BUTTON_LEFT) {
      SDL_HideCursor();
      saved_cursor_position.x = ev->button.x;
      saved_cursor_position.y = ev->button.y;
    }
  } else if (ev->type == SDL_EVENT_MOUSE_BUTTON_UP) {
    if (ev->button.button == SDL_BUTTON_LEFT) {
      SDL_ShowCursor();
    }
  } else if (ev->type == SDL_EVENT_MOUSE_MOTION) {
    if (ev->motion.state & SDL_BUTTON_LMASK) {
      render->camera.rotation.yaw += (ev->motion.x - saved_cursor_position.x) / 5.f;
      render->camera.rotation.pitch += (ev->motion.y - saved_cursor_position.y) / 5.f;

      render->camera.rotation.pitch = render->camera.rotation.pitch > 90 ? 90 : render->camera.rotation.pitch;
      render->camera.rotation.pitch = render->camera.rotation.pitch < -90 ? -90 : render->camera.rotation.pitch;

      SDL_WarpMouseInWindow(state->window, saved_cursor_position.x, saved_cursor_position.y);
    }
  }
})


on_event(EVENT_TYPE_RENDER_EVENT, {
  struct renderer_t *render = event->renderer;
  appstate_t *state = (appstate_t *)event->appstate;

  float time = SDL_GetTicks() / 1000.f;

  renderer_fill((struct vec4f_t){0.0f, 0.1f, 0.2f, 1.0f}, 
                GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  renderer_set_shader(render, render->default_3d);

  struct matrix_4x4f_t line_model;
  matrix_4x4f_identity(&line_model);

  shader_uniform_mat4x4f(render->current_shader, "view", &render->camera.view_matrix);
  shader_uniform_mat4x4f(render->current_shader, "projection", &render->camera.projection_matrix);

  renderer_triangle(render, (struct triangle_t){
    {0, 1, 0},
    {1, -1, 0},
    {-1, -1, 0},
    {1, 1, 1, 1}
  });

  shader_uniform_mat4x4f(render->current_shader, "model", &line_model);
  
  renderer_line(render, (struct line_t) {
         {0, 0, 0},
         {0, 2, 0},
         {0, 1, 0, 1},
         2
  });

  renderer_line(render, (struct line_t) {
         {0, 0, 0},
         {0, 0, 2},
         {0, 0, 1, 1},
         2
  });

  renderer_line(render, (struct line_t) {
         {0, 0, 0},
         {2, 0, 0},
         {1, 0, 0, 1},
         2
  });
})
