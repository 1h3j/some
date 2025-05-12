#ifndef EVENTS_H
#define EVENTS_H

#include "render/renderer.h"
#include <SDL3/SDL_events.h>

typedef struct {
  void **ptrs;
  int size;
} callback_array_t;

typedef struct {
  struct renderer_t *renderer;
  SDL_Event *sdl_event;
  void* appstate;
} event_info_t;

callback_array_t *callback_array_create();

void callback_array_append(void* ptr, callback_array_t *arr);

void create_event(callback_array_t *event_type, event_info_t *info);

void callback_array_free(callback_array_t *arr);

#define CONCAT_IMPL(a, b) a##b
#define MACRO_CONCAT(a, b) CONCAT_IMPL(a, b)

#define EVENT_HANDLER(event_type, id, logic) void id (event_info_t *event) logic __attribute__((constructor)) static void MACRO_CONCAT(register_event_handler_, __COUNTER__)() { callback_array_append(&id, event_type ); }

#define on_event(event_type, logic) EVENT_HANDLER(event_type, MACRO_CONCAT(event_handler_, __COUNTER__), logic)

#define create_event_listener(event_type) callback_array_t *event_type; __attribute__((constructor)) static void MACRO_CONCAT(event_listener_constructor_, __COUNTER__)() { event_type = callback_array_create(); } static void MACRO_CONCAT(event_listener_deconstructor_, __COUNTER__)() { callback_array_free(event_type); }
#define define_event_listener(event_type) extern callback_array_t *event_type;

#endif // EVENTS_H
