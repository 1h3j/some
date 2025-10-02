#include "app/appstate.h"
#include "event/events.h"
#include "event/callback.h"
#include "glad/glad.h"
#include "math/angles.h"
#include "math/matrix.h"
#include "render/renderer.h"
#include "render/primitives.h"
#include "render/shader.h"

#include "math/transform.h"
#include "math/camera.h"

Shader *shader;
ObjectQuad *quad;
Camera *camera;

TransformF transformation;

on_event(EVENT_TYPE_INIT_EVENT, {
  AppState *state = (AppState *)event->appstate;

  shader = create_shader(RENDERER_3D_DEFAULT_VSH_S, RENDERER_3D_DEFAULT_FSH_S);
  quad = quad_create((PrimitiveQuad){
    { {-0.5, 0.5, 0}, 
      { 0.5, 0.5, 0}, 
      { 0.5,-0.5, 0},
      {-0.5,-0.5, 0} },

    {1, 0, 0, 1}
  });

  camera = camera_create(state->width, state->height);
  camera->position.z = 2;

  glEnable(GL_DEPTH_TEST);
})

on_event(EVENT_TYPE_QUIT_EVENT, {
  camera_free(camera);
  quad_destroy(quad);
  free_shader(shader);
})

on_event(EVENT_TYPE_SDL_EVENT, {
  AppState* appstate = (AppState *)event->appstate;

  if (event->sdl_event->type == SDL_EVENT_QUIT) {
    appstate->appstatus_e = APPSTATUS_EXIT_SUCCESS;
  } if (event->sdl_event->type == SDL_EVENT_WINDOW_RESIZED) {
    camera->width  = event->sdl_event->window.data1;
    camera->height = event->sdl_event->window.data2;
  }
})

on_event(EVENT_TYPE_RENDER_EVENT, {
  render_clear_with_depth((Vec4f){0.05f, 0.1f, 0.1f, 1.f});

  matrix_4x4f_identity(&transformation);
  transform_f_rotate_z(&transformation, degrees_to_radians(180.f * SDL_GetTicks() / 1000.f));
  transform_f_rotate_x(&transformation, degrees_to_radians(70.f * SDL_GetTicks() / 1000.f));
  transform_f_rotate_y(&transformation, degrees_to_radians(40.f * SDL_GetTicks() / 1000.f));

  shader_uniform_mat4x4f(shader, "model", &transformation);

  camera_calculate_matrices(camera);
  camera_set_shader_matrices(camera, shader, "view", "projection");

  shader_use(shader);
  quad_draw(quad); 
})
