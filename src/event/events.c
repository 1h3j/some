#include "events.h"
#include <stdlib.h>

callback_array_t *callback_array_create() {
  callback_array_t *arr = (callback_array_t *)malloc(sizeof(callback_array_t));

  arr->ptrs = malloc(sizeof(void *));
  arr->size = 0;

  return arr;
}

void callback_array_append(void* ptr, callback_array_t *arr) {
  if (arr->size != 0) arr->ptrs = (void**)realloc(arr->ptrs, (arr->size + 1) * sizeof(void*));
  arr->ptrs[arr->size++] = ptr;
}

void create_event(callback_array_t *event_type, event_info_t *info) {
  for (int i = 0; i < event_type->size; i++) {
    if (event_type->ptrs[i] == NULL) continue;

    ((void (*)(event_info_t *))(event_type->ptrs[i]))(info);
  }
}

void callback_array_free(callback_array_t *arr) {
  free(arr->ptrs);
  free(arr);
}
