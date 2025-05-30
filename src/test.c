#include "app/appstate.h"
#include "event/events.h"
#include "event/callback.h"
#include "render/renderer.h"
#include "render/primitives.h"
#include "render/shader.h"

Shader *shader;
ObjectQuad *quad;

on_event(EVENT_TYPE_INIT_EVENT, {
  shader = create_shader(RENDERER_2D_DEFAULT_VSH_S, RENDERER_2D_DEFAULT_FSH_S);
  quad = quad_create((PrimitiveQuad){
    { {-0.5, 0.5, 0}, 
      { 0.5, 0.5, 0}, 
      { 0.5,-0.5, 0},
      {-0.5,-0.5, 0}},
    {1, 0, 0, 1}
  });
})

on_event(EVENT_TYPE_QUIT_EVENT, {
  quad_destroy(quad);
  free_shader(shader);
})

on_event(EVENT_TYPE_SDL_EVENT, {
  AppState* appstate = (AppState *)event->appstate;

  if (event->sdl_event->type == SDL_EVENT_QUIT) {
    appstate->appstatus_e = APPSTATUS_EXIT_SUCCESS;
  }
})

on_event(EVENT_TYPE_RENDER_EVENT, {
  render_clear((Vec4f){0.05f, 0.1f, 0.1f, 1.f});

  shader_use(shader);

  quad_draw(quad); 
})
