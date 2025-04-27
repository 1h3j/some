#include "glad/glad.h"
#include "math/angles.h"
#include "math/camera.h"
#include "math/matrix.h"
#include "math/vectors.h"
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
  r->shader_0 =
      load_shader("assets/shaders/position.vsh", "assets/shaders/position.fsh");
}

void clean_resources(struct __resources_t *r) { free_shader(r->shader_0); }

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  *appstate = (void *)malloc(sizeof(struct appstate_t));
  struct appstate_t *state = (struct appstate_t *)(*appstate);

  // > No error checking
  //      ⠀⠀⠀⠀⠀⠀⢀⣴⠶⠶⠶⠶⠶⢶⢶⡶⡶⢶⣶⣶⡶⡶⡶⣶⣶⣶⣤⣤⣀⣀⠀⠀⠀⠀⠀⠀
  //      ⠀⠀⠀⠀⠀⣴⠏⠁⠀⣀⡰⣒⡭⣽⣒⣒⣒⣒⡒⠲⠲⠮⠯⠭⠷⠽⠽⠽⠭⠛⠷⣦⣀⠀⠀⠀
  //      ⠀⠀⠀⠀⣼⠏⠀⠰⠚⡱⡪⠗⠉⠉⠀⠀⠀⠈⢇⠀⠀⠀⠀⢪⠋⠉⠉⠙⠲⡄⠀⠈⢹⡇⠀⠀
  //      ⠀⠀⣠⣾⢇⠀⠀⠀⡈⡈⣡⣶⣾⣿⣿⡟⠷⣶⣄⠀⠀⠀⠀⠂⣠⣤⣴⣤⣄⢁⠀⠀⠘⣷⣄⠀
  //      ⢠⣾⡟⢙⣹⣽⢵⣬⣝⢂⠛⠛⢙⣽⠏⠛⠷⣮⠿⠃⠀⠐⢶⣿⠿⠛⠛⠛⠙⠉⡙⡙⡽⡪⣟⣧
  //      ⡟⢱⢡⣾⠃⢀⣶⣌⡙⠙⠛⠛⠛⠁⠀⠀⡀⢀⢀⠀⠀⠀⠈⣿⣄⠀⠀⢶⡴⡾⢛⠙⠻⢸⢸⣿
  //      ⣷⣸⡘⣧⡚⠻⣯⡙⠛⢷⣦⣦⣄⡒⡒⠋⢽⡟⣭⣤⣄⠀⠀⠀⣹⣿⡦⣄⠀⢀⣾⣇⢀⣪⣼⡿
  //      ⠘⢧⣕⡮⠅⠀⠹⣿⣷⣤⣿⣌⠉⠛⠻⢶⣮⣷⣬⣀⣀⣐⠳⢞⠋⣀⣀⣤⣵⣿⢿⣿⠈⢠⡿⠁
  //      ⠀⠈⠻⣧⡀⠀⠀⠘⢷⡌⣿⠿⢿⣷⣦⣾⣇⣀⠈⠙⣿⠛⠛⣻⡟⠛⢙⣿⣀⣿⣼⣿⠇⢸⡇⠀
  //      ⠀⠀⠀⠙⣧⡄⠀⠀⠀⠙⢿⣄⡀⠀⢹⡟⠛⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⢺⡇⠀
  //      ⠀⠀⠀⠀⠘⢻⣦⡀⣄⡠⣀⡙⠻⢶⣾⣃⡀⠀⠀⢸⡇⠉⢉⣿⠋⢹⡟⢹⣟⣹⣿⠏⠀⢸⡇⠀
  //      ⠀⠀⠀⠀⠀⠀⠈⠻⢶⣭⣚⠮⣑⡦⢅⣍⠛⠛⠟⠟⠗⠷⠿⠿⠞⠟⠟⠟⠛⢋⡄⠀⠀⢸⡇⠀
  //      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠿⢶⣭⣕⡳⠫⠾⢶⣶⣲⡨⠬⠬⠬⠤⠤⠴⠒⠋⣀⡔⠇⢸⡇⠀
  //      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠻⢶⣦⣄⣄⣁⠉⠉⠉⠉⠉⠉⠉⠉⠉⠁⠀⢀⣼⠇⠀
  //      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠛⠻⠳⠶⠶⣦⣤⣤⣤⣤⠶⠶⠛⠁⠀⠀

  // I added error checking but I'm keepping the art

  // > Error checking
  //  ⠀⠀⠀⢀⣠⠤⠶⠖⠒⠛⠉⠉⠉⠉⠉⢉⠩⠭⣉⠉⠉⠙⠲⣄⠀⠀⠀⠀⠀
  // ⠀⠀⢠⠞⠉⠀⣀⠀⠀⠀⠀⠀⠀⠀⢀⠔⠚⠛⠩⠖⣯⣒⢄⠀⠈⢣⡀⠀⠀⠀
  // ⠀⢀⡾⠀⠀⠜⠁⠀⠀⠀⠀⠀⠀⠀⠈⣀⣤⣤⣤⣤⣈⠋⠑⠀⠀⠀⢳⡀⠀⠀
  // ⣴⣿⣴⠒⠂⠘⠛⠛⠻⠿⣶⡄⠀⠀⢿⣥⠴⠚⢿⠛⠛⠃⢞⣆⣤⣤⡚⠻⣦⡀
  // ⣿⡃⠓⠋⠙⠷⠤⠂⠀⣠⡟⠀⠀⠀⢀⣀⠀⠀⠈⠙⠓⠛⠉⠁⠀⠀⠙⡆⠃⢳
  // ⢻⡷⠅⠀⠀⠀⢀⠴⠺⢧⡀⠀⠠⠴⠮⢹⠏⠁⠀⠀⠀⠀⠀⠀⠀⠀⠠⠇⡆⣼
  // ⠀⢿⠀⠀⠀⢀⣀⣤⣤⣤⢽⣥⠤⢤⣤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢭⠞⠁
  // ⠀⢸⠀⠀⣼⣿⣹⣇⣼⣁⣸⣇⡀⢸⡇⠀⠈⢙⡷⠦⣄⠈⠑⢄⠀⠀⢠⡏⠀⠀
  // ⠀⢸⠀⢰⣿⣿⣿⣿⠿⠿⣿⠿⢿⡿⠿⢶⣦⣼⣄⡀⠈⣷⣄⠀⠀⠀⠸⡆⠀⠀
  // ⠀⣼⠀⢸⣿⣿⣀⡿⠤⠶⠿⠶⠴⠷⢤⣀⣠⡟⠙⠛⠷⣿⣌⣳⡀⠀⠀⢻⡀⠀
  // ⠀⢿⠀⠈⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠈⠁⠈⠉⠓⠲⠦⣿⡀⠙⢻⡆⠀⠈⣧⠀
  // ⠀⠘⢧⣀⠘⠀⠀⠀⣀⣠⠤⠴⠶⠶⠦⢤⣄⣀⠀⠀⠀⠀⠉⠓⢶⡟⠁⠀⣿⠀
  // ⠀⠀⠀⠈⠉⠛⠋⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠓⠶⢤⣄⣀⣀⣀⣀⡴⠃⠀
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
  state->renderer->camera.width = WINDOW_WIDTH;
  state->renderer->camera.height = WINDOW_HEIGHT;

  state->renderer->camera.clip_near = 0.01;
  state->renderer->camera.clip_far = 100.0;

  state->renderer->camera.field_of_view = 90.f;
  state->renderer->camera.zoom = 1;
  state->renderer->camera.position = (struct vec3f_t){0, 0, 2.f};
  state->renderer->camera.rotation = (struct rotation_t){0, 0, 0};
  state->renderer->camera.projection_type = PROJECTION_TYPE_ORTHO;

  glGenVertexArrays(1, &state->resources.test_vao);
  glGenBuffers(1, &state->resources.test_vbo);

  glBindVertexArray(state->resources.test_vao);
  glBindBuffer(GL_ARRAY_BUFFER, state->resources.test_vbo);
  struct vec3f_t points[3] = {
      {0, 0.5f, 0}, {0.5f, -0.5f, 0}, {-0.5f, -0.5f, 0}};

  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vec3f_t),
                        (void *)0);
  glEnableVertexAttribArray(0);
  shader_uniform_vec4f(state->resources.shader_0, "color",
                       (struct vec4f_t){1.f, 0.f, 0.f, 1.f});

  // glEnable(GL_DEBUG_OUTPUT_KHR);

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  struct appstate_t *state = (struct appstate_t *)appstate;
  struct camera_t *camera = &state->renderer->camera;
  glClearColor(0, 0.1, 0.2, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  renderer_set_shader(state->renderer, state->resources.shader_0);

  camera_calculate_matrices(camera);

  shader_uniform_mat4x4f(state->resources.shader_0, "view",
                         &camera->view_matrix);
  shader_uniform_mat4x4f(state->resources.shader_0, "projection",
                         &camera->projection_matrix);

  struct matrix_4x4f_t model;
  matrix_4x4f_identity(&model);

  shader_uniform_mat4x4f(state->resources.shader_0, "model", &model);

  glBindVertexArray(state->resources.test_vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  renderer_line(
      state->renderer,
      (struct line_t){{0, 0, 1}, {0, 1, 1}, {1.0, 0.0, 0.0, 1.0}, 5.0});

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
