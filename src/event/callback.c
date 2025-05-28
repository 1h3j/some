#include "callback.h"
#include "events.h"

#include "app/appstate.h"
#include "glad/glad.h"
#include "render/renderer.h"
#include "util/logging.h"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h> 
#include <SDL3/SDL_video.h>

AppState state;
EventInfo info;
SDL_Event ev;

create_event_listener(EVENT_TYPE_RENDER_EVENT);

create_event_listener(EVENT_TYPE_SDL_EVENT);

create_event_listener(EVENT_TYPE_INIT_EVENT);
create_event_listener(EVENT_TYPE_QUIT_EVENT);

int main(int argc, char** argv) {
  if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
    log_fatal("SDL_InitSubSystem failed: %s", SDL_GetError());
    return -1;
  }

  log_info("SDL_InitSubSystem ran successfully");

  state.window = SDL_CreateWindow("SomeEngine", 
                                  WINDOW_WIDTH, WINDOW_HEIGHT, 
                                  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (state.window == NULL) {
    log_fatal("SDL_CreateWindow failed: %s", SDL_GetError());
    return -1;
  }

  log_info("SDL_CreateWindow ran successfully");

  SDL_GL_SetSwapInterval(0);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MINOR); 
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  state.renderer = renderer_create(state.window);
  if (state.renderer->gl == NULL) {
    log_fatal("SDL_GL_CreateContext failed");
    return -1;
  }

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    log_fatal("Failed to load OpenGL");
    return -1;
  }

  log_info("Running OpenGL %d.%d", GL_MAJOR, GL_MINOR);

  info.renderer = state.renderer;
  info.appstate = &state;
  info.sdl_event = &ev;

  state.width = WINDOW_WIDTH;
  state.height = WINDOW_HEIGHT;


  create_event(EVENT_TYPE_INIT_EVENT, &info);

  while (state.appstatus_e == APPSTATUS_CONTINUE) {
    create_event(EVENT_TYPE_RENDER_EVENT, &info);
    SDL_GL_SwapWindow(state.window);

    while (SDL_PollEvent(&ev)) {
      create_event(EVENT_TYPE_SDL_EVENT, &info);
      if (ev.type == SDL_EVENT_WINDOW_RESIZED) {
        state.width = ev.window.data1;
        state.height = ev.window.data2;
        
        glViewport(0, 0, state.width, state.height); }
    }
  }

  create_event(EVENT_TYPE_QUIT_EVENT, &info);

  if (state.appstatus_e == APPSTATUS_EXIT_SUCCESS) {
    renderer_destroy(state.renderer);
    SDL_DestroyWindow(state.window);
    log_info("Program finished successfully");
  } else if (state.appstatus_e == APPSTATUS_EXIT_FAILURE) {
    log_error("Program finished unsuccessfully");
  }

  SDL_Quit();
}
