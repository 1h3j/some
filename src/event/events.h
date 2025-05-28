#ifndef EVENTS_H
#define EVENTS_H

#include "render/renderer.h"
#include <SDL3/SDL_events.h>

typedef struct {
  void **ptrs;
  int size;
} FuncPtrArr;

typedef struct {
  Renderer *renderer;
  SDL_Event *sdl_event;
  void* appstate;
} EventInfo;

/**
 * Creates a function pointer array
 *
 * @return Pointer to an allocated callback array
*/
FuncPtrArr *callback_array_create();

/**
 * Appends a function pointer to the callback array.
 *
 * @param ptr Pointer to a function.
 * @param arr Pointer to callback array
*/
void callback_array_append(void* ptr, FuncPtrArr *arr);

/**
 * Calls all the functions associated with the callback array.
 *
 * @param event_type The callback array used.
 * @param info       Info to be sent to the functions.
*/
void create_event(FuncPtrArr *event_type, EventInfo *info);

/**
 * Frees resources used by the callback array.
 *
 * @param arr Pointer to the callback array
*/
void callback_array_free(FuncPtrArr *arr);

/**
 * Implicit concatenation
*/
#define CONCAT_IMPL(a, b) a##b

/**
 * Macro concatenation
*/
#define MACRO_CONCAT(a, b) CONCAT_IMPL(a, b)

#define EVENT_HANDLER(event_type, id, logic) void id (EventInfo *event) logic __attribute__((constructor)) static void MACRO_CONCAT(register_event_handler_, __COUNTER__)() { callback_array_append(&id, event_type ); }

/**
 * Defines a function that becomes called once the event is signaled.
 *
 * @param event_type Callback array / event type
 * @param logic      Must be enclosed in braces in order for it to work. Event info is stored in variable event, which isn't seen anywhere else.
*/
#define on_event(event_type, logic) EVENT_HANDLER(event_type, MACRO_CONCAT(event_handler_, __COUNTER__), logic)

/**
 * Creates a callback array. Must be placed in a source file.
*/
#define create_event_listener(event_type) FuncPtrArr *event_type; __attribute__((constructor)) static void MACRO_CONCAT(event_listener_constructor_, __COUNTER__)() { event_type = callback_array_create(); } __attribute__((destructor)) static void MACRO_CONCAT(event_listener_destructor_, __COUNTER__)() { callback_array_free(event_type); }

/**
 * Defines a callback array. This must be called first in a header file before calling create_event_listener.
*/
#define define_event_listener(event_type) extern FuncPtrArr *event_type;

#endif // EVENTS_H
